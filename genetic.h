//
// Created by kamil on 06.07.18.
//

#ifndef GENETIC_GENETIC_H
#define GENETIC_GENETIC_H

#include "graph.h"

struct Population;

typedef struct {
    int* genome;
    struct Population* population;

} Individual;

typedef struct Population {
    int genome_length;
    float mutation_rate;
    int population_size;
    Individual* individuals;
    Individual* next_iteration_individuals;

    //instance of a problem
    Graph* graph;
} Population;

Individual create_individual(int* genome, Population* population);
Individual* reproduce(Individual individual1, Individual individual2, int crossover_index);
int mutate(Individual* individual);
int get_fitness(Individual);
int get_impossible_transition_penalty(Population);
int get_start_penalty(Population);
int get_destination_penalty(Population);
#endif //GENETIC_GENETIC_H
