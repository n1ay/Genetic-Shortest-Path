//
// Created by kamil on 06.07.18.
//

#include <stdlib.h>
#include <sodium.h>
#include <memory.h>
#include "genetic.h"

individual* reproduce(individual individual1, individual individual2, int crossover_index) {
    individual* childs = malloc(2* sizeof(individual));
    int genome_length = individual1.population->genome_length;

    individual child1, child2;
    child1.population = individual1.population;
    child2.population = individual2.population;

    int* genome1 = malloc(genome_length*sizeof(char));
    int* genome2 = malloc(genome_length*sizeof(char));
    memcpy(genome1, individual1.genome, (size_t) crossover_index*sizeof(int));
    memcpy(genome1+crossover_index, individual2.genome+crossover_index, (size_t) (genome_length - crossover_index)*sizeof(int));
    memcpy(genome2, individual2.genome, (size_t) crossover_index*sizeof(int));
    memcpy(genome2+crossover_index, individual1.genome+crossover_index, (size_t) (genome_length - crossover_index)*sizeof(int));

    child1.genome = genome1;
    child2.genome = genome2;

    childs[0] = child1;
    childs[1] = child2;

    return childs;
}
