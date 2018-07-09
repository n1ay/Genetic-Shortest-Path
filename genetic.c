//
// Created by kamil on 06.07.18.
//

#include <stdlib.h>
#include <sodium.h>
#include <memory.h>
#include "genetic.h"
#include "graph.h"
#include <string.h>

double* generate_roulette(Population population) {
    double fitness_sum = 0;
    double* individual_fitness = malloc(sizeof(double)*(population.population_size));
    for(int i=0; i<population.population_size; i++) {
        individual_fitness[i] = get_fitness(population.individuals[i]);
        fitness_sum += individual_fitness[i];
    }
    double * roulette_ranges = malloc(sizeof(double)*(population.population_size+1));
    roulette_ranges[0] = 0.0;
    double accumulated_fitness = 0;
    for(int i=0; i<population.population_size; i++) {
        accumulated_fitness += individual_fitness[i]/fitness_sum;
        roulette_ranges[i+1] = accumulated_fitness;
    }

    free(individual_fitness);
    return roulette_ranges;
}

int roulette_wheel_select_candidate(Population population, const double* roulette_ranges) {
    double random_number;
    random_number = 1.0 * randombytes_uniform(INT32_MAX) / INT32_MAX;
    for(int j=0; j<population.population_size; j++) {
        if(random_number>roulette_ranges[j] && random_number <= roulette_ranges[j+1])
            return j;
    }
    return population.population_size-1;
}

int* roulette_wheel_get_parents(Population* population) {
    double * roulette_ranges = generate_roulette(*population);
    int* parents = malloc(sizeof(int)*population->population_size/2);
    int* selected_candidates = malloc(sizeof(int)*population->population_size);
    memset(selected_candidates, 0, sizeof(int)*population->population_size);
    for(int i=0; i<population->population_size/2; i++) {
        int candidate = roulette_wheel_select_candidate(*population, roulette_ranges);
        while(selected_candidates[candidate]) {
            candidate = roulette_wheel_select_candidate(*population, roulette_ranges);
        }
        selected_candidates[candidate] = 1;
        parents[i] = candidate;
    }
    free(roulette_ranges);
    free(selected_candidates);
    return parents;
}

void roulette_wheel_reproduction(Population* population) {
    int * parents = roulette_wheel_get_parents(population);
    int* selected_candidates = malloc(sizeof(int)*population->population_size);
    memset(selected_candidates, 0, sizeof(int)*population->population_size);
    for(int i=0; i<population->population_size/2; i++) {
        selected_candidates[parents[i]] = 1;
    }

    Individual* children;
    int i=0;
    for (int j = 0; j < population->population_size/2; j+=2) {
        children = reproduce_apply_genetic_operators(population->individuals[j], population->individuals[j+1]);
        for (int k = 0; k < 2; ++k) {
            while(selected_candidates[i])
                i++;
            free(population->individuals[i].genome);
            population->individuals[i] = children[k];
        }
    }
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
    int gene_to_mutate = randombytes_uniform((const uint32_t) ((individual->population)->genome_length-1))+1;
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

Individual get_best_individual(Population population) {
    double best_fitness = 0;
    Individual best_individual = population.individuals[0];

    double fitness;
    for (int i = 0; i < population.population_size; ++i) {
        fitness = get_fitness(population.individuals[i]);
        if(fitness > best_fitness) {
            best_fitness = fitness;
            best_individual = population.individuals[i];
        }
    }

    return best_individual;
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

double get_value_from_fitness(double fitness) {
    return (1 - fitness)/fitness;
}

Individual create_individual(int* genome, Population* population) {
    Individual individual;
    individual.genome = genome;
    individual.population = population;
    return individual;
}

Population* create_population(Graph* graph, int population_size, double mutation_rate, double crossover_rate) {
    if(population_size%2)
        fprintf(stderr, "Population size should be divisible by 2");
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
        genome[0] = graph->path.id_from;
        for (int j = 1; j < population->genome_length; ++j) {
            int gene = randombytes_uniform((const uint32_t) population->genome_length);
            while (gene == graph->path.id_from)
                gene = randombytes_uniform((const uint32_t) population->genome_length);

            genome[j] = gene;
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

