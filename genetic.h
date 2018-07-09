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
    double mutation_rate;
    double crossover_rate;
    int population_size;
    Individual* individuals;

    //instance of a problem
    Graph* graph;
} Population;

double* generate_roulette(Population population);
Population* create_population(Graph* graph, int population_size, double mutation_rate, double crossover_rate);
void delete_population(Population* population);
Individual create_individual(int* genome, Population* population);
void delete_individuals(Individual* individuals);

int roulette_wheel_select_candidate(Population population, const double* roulette_ranges);
void roulette_wheel_reproduction(Population* population);
int* roulette_wheel_get_parents(Population* population);
Individual* reproduce(Individual individual1, Individual individual2, int crossover_index);
Individual* reproduce_apply_genetic_operators(Individual individual1, Individual individual2);
int mutate(Individual* individual);

Individual get_best_individual(Population);
double get_fitness(Individual);
int get_impossible_transition_penalty(Population);
int get_start_penalty(Population);
int get_destination_penalty(Population);
double get_value_from_fitness(double fitness);
#endif //GENETIC_GENETIC_H
