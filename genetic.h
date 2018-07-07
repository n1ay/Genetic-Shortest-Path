//
// Created by kamil on 06.07.18.
//

#ifndef GENETIC_GENETIC_H
#define GENETIC_GENETIC_H

struct population;

typedef struct {
    int* genome;
    struct population* population;

} individual;

typedef struct population {
    int genome_length;
    float mutation_rate;
    int population_size;
    individual* individuals;
    individual* next_iteration_individuals;
} population;

individual* reproduce(individual individual1, individual individual2, int crossover_index);

#endif //GENETIC_GENETIC_H
