//
// Created by kamil on 06.07.18.
//

#include <stdlib.h>
#include <sodium.h>
#include <memory.h>
#include "genetic.h"
#include "graph.h"

Individual* reproduce(Individual individual1, Individual individual2, int crossover_index) {
    int genome_length = individual1.population->genome_length;

    int* genome1 = malloc(genome_length*sizeof(int));
    int* genome2 = malloc(genome_length*sizeof(int));
    memcpy(genome1, individual1.genome, (size_t) crossover_index*sizeof(int));
    memcpy(genome1+crossover_index, individual2.genome+crossover_index, (size_t) (genome_length - crossover_index)*sizeof(int));
    memcpy(genome2, individual2.genome, (size_t) crossover_index*sizeof(int));
    memcpy(genome2+crossover_index, individual1.genome+crossover_index, (size_t) (genome_length - crossover_index)*sizeof(int));

    Individual* children = malloc(2* sizeof(Individual));
    Individual child1, child2;
    child1.population = individual1.population;
    child2.population = individual2.population;
    child1.genome = genome1;
    child2.genome = genome2;

    children[0] = child1;
    children[1] = child2;

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

int get_fitness(Individual individual) {
    int fitness = 0;
    int weight;
    if(individual.genome[0] != individual.population->graph->path.id_from)
        fitness+=get_start_penalty(*individual.population);
    for(int i=0; i<individual.population->graph->edges_number; i++) {
        //TODO:
        fitness+=0;
    }
    return fitness;
}

int get_impossible_transition_penalty(Population population) {
    return -10*get_all_weights_sum(*population.graph);
}

int get_start_penalty(Population population) {
    return get_impossible_transition_penalty(population)*population.graph->vertices_number;
}

int get_destination_penalty(Population population) {
    return get_impossible_transition_penalty(population)*population.graph->vertices_number;
}
