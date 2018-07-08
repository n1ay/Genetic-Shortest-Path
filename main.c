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
    Population* population = create_population(&graph, 4*2, 0.05, 0.1);


    delete_population(population);
    return 0;
}
