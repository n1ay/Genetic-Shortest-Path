//
// Created by kamil on 06.07.18.
//

#include <stdlib.h>
#include <sodium.h>
#include <memory.h>
#include "genetic.h"
#include "graph.h"

Individual* roulette_wheel_selection(Population* population) {
    return NULL;
}

Individual* roulette_wheel_reproduction(Population* population, Individual* next_generation) {
    return NULL;
}

Individual* reproduce_apply_genetic_operators(Individual individual1, Individual individual2) {
    Individual* children;
    double random_number = 1.0 * randombytes_uniform(INT32_MAX) / INT32_MAX;
    if(random_number < individual1.population->crossover_rate) {
        int crossover_index = randombytes_uniform((const uint32_t) (individual1.population->genome_length - 2)) + 1;
        children = reproduce(individual1, individual2, crossover_index);
    } else {
        children = reproduce(individual1, individual2, 0);
    }

    for(int i=0; i<2; i++) {
        random_number = 1.0 * randombytes_uniform(INT32_MAX) / INT32_MAX;
        if (random_number < individual1.population->mutation_rate) {
            mutate(&children[i]);
        }
    }
    return children;
}

Individual* reproduce(Individual individual1, Individual individual2, int crossover_index) {
    int genome_length = individual1.population->genome_length;

    int* genome1 = malloc(genome_length*sizeof(int));
    int* genome2 = malloc(genome_length*sizeof(int));
    memcpy(genome1, individual1.genome, (size_t) crossover_index*sizeof(int));
    memcpy(genome1+crossover_index, individual2.genome+crossover_index, (size_t) (genome_length - crossover_index)*sizeof(int));
    memcpy(genome2, individual2.genome, (size_t) crossover_index*sizeof(int));
    memcpy(genome2+crossover_index, individual1.genome+crossover_index, (size_t) (genome_length - crossover_index)*sizeof(int));

    Individual* children = malloc(2* sizeof(Individual));

    children[0] = create_individual(genome1, individual1.population);
    children[1] = create_individual(genome2, individual2.population);;

    return children;
}

int mutate(Individual* individual) {
    int gene_to_mutate = randombytes_uniform((const uint32_t) ((individual->population)->genome_length));
    int new_gene = randombytes_uniform((const uint32_t) ((individual->population)->genome_length));
    while(new_gene == individual->genome[gene_to_mutate])
        new_gene = randombytes_uniform((const uint32_t) ((individual->population)->genome_length));
    individual->genome[gene_to_mutate] = new_gene;

    return gene_to_mutate;
}

double get_fitness(Individual individual) {
    int inverse_fitness = 1;
    int cheated = 0;
    if(individual.genome[0] != individual.population->graph->path.id_from) {
        inverse_fitness += get_start_penalty(*individual.population);
        cheated = 1;
    }

    int destination_index=-1;
    for(int i=0; i<individual.population->graph->edges_number; i++) {
        if(individual.population->graph->path.id_to == individual.genome[i]) {
            destination_index = i;
            break;
        }
    }
    if(destination_index == -1) {
        inverse_fitness += get_destination_penalty(*individual.population);
    }

    int weight;
    int reached_destination = 0;
    for(int i=0; i<individual.population->genome_length-1; i++) {
        Vertex from = create_vertex(individual.genome[i]), to = create_vertex(individual.genome[i+1]);
        Edge edge = create_edge(0, 0, &from, &to);
        weight = get_edge_weight(edge, *individual.population->graph);
        if(weight == -1) {
            inverse_fitness += get_impossible_transition_penalty(*individual.population);
            cheated = 1;
        } else {
            inverse_fitness += weight;
            if(individual.population->graph->path.id_to == to.id) {
                reached_destination = 1;
            }
        }
        if(reached_destination && !cheated)
            break;
    }
    return 1.0/inverse_fitness;
}

int get_impossible_transition_penalty(Population population) {
    return 10*get_all_weights_sum(*population.graph);
}

int get_start_penalty(Population population) {
    return get_impossible_transition_penalty(population)*population.graph->vertices_number;
}

int get_destination_penalty(Population population) {
    return get_impossible_transition_penalty(population)*population.graph->vertices_number;
}

Individual create_individual(int* genome, Population* population) {
    Individual individual;
    individual.genome = genome;
    individual.population = population;
    return individual;
}

Population* create_population(Graph* graph, int population_size, float mutation_rate, float crossover_rate) {
    Population* population = malloc(sizeof(Population));
    population->graph = graph;
    population->genome_length = graph->vertices_number;
    population->population_size = population_size;
    population->mutation_rate = mutation_rate;
    population->crossover_rate = crossover_rate;
    population->individuals = malloc(population_size*sizeof(Individual));
    int* genome;
    for(int i=0; i<population_size; i++) {
        genome = malloc(sizeof(int)*population->genome_length);
        for (int j = 0; j < population->genome_length; ++j) {
            genome[j] = randombytes_uniform((const uint32_t) population->genome_length);
        }
        population->individuals[i] = create_individual(genome, population);
    }
    return population;
}

void delete_individuals(Individual* individuals) {
    for(int i=0; i<individuals[0].population->population_size; i++)
        free(individuals[i].genome);
    free(individuals);
}

void delete_population(Population* population) {
    delete_graph(*population->graph);
    delete_individuals(population->individuals);
    free(population);
}

