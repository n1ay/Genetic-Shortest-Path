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
    float crossover_rate;
    int population_size;
    Individual* individuals;

    //instance of a problem
    Graph* graph;
} Population;

Population* create_population(Graph* graph, int population_size, float mutation_rate, float crossover_rate);
void delete_population(Population* population);
Individual* roulette_wheel_selection(Population* population);
Individual* roulette_wheel_reproduction(Population* population, Individual* next_generation);
Individual create_individual(int* genome, Population* population);
Individual* reproduce(Individual individual1, Individual individual2, int crossover_index);
Individual* reproduce_apply_genetic_operators(Individual individual1, Individual individual2);
void delete_individuals(Individual* individuals);
int mutate(Individual* individual);
double get_fitness(Individual);
int get_impossible_transition_penalty(Population);
int get_start_penalty(Population);
int get_destination_penalty(Population);
#endif //GENETIC_GENETIC_H
