#include <stdio.h>
#include <stdlib.h>
#include <sodium.h>
#include "graph.h"
#include "genetic_test.h"
#include "graph_test.h"
#include "genetic.h"

void tests(void) {
    genetic_test();
    graph_test();
}

#define PERFORM_TESTS 1

int main(void) {
    sodium_init();

    if(PERFORM_TESTS == 1)
        tests();

    Graph graph = build_exemplary_graph();
    Population* population = create_population(&graph, 128, 0, 0);

    double best_fitness = 0;
    Individual best_individual;
    int iterations = 1000;
    Individual individual;
    double fitness;
    for (int i = 0; i < iterations; ++i) {
        individual = get_best_individual(*population);
        fitness = get_fitness(individual);
        if(fitness > best_fitness) {
            best_fitness = fitness;
            best_individual = individual;
        }
        roulette_wheel_reproduction(population);
    }

    printf("Best path: \n");
    for (int j = 0; j < population->genome_length; ++j) {
        printf("%d ", best_individual.genome[j]);
    }
    printf("\nBest path length: %lf\n", get_value_from_fitness(best_fitness));

    delete_population(population);
    return 0;
}
