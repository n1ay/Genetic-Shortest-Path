#include <stdio.h>
#include <stdlib.h>
#include <sodium.h>
#include "graph.h"
#include "genetic_test.h"
#include "graph_test.h"

void tests(void) {
    genetic_test();
    graph_test();
}

#define PERFORM_TESTS 1

int main(void) {
    sodium_init();

    if(PERFORM_TESTS == 1)
        tests();

    Graph g = build_exemplary_graph();

    for(int i=0; i<g.vertices_number; i++)
        printf("%d\n", g.vertices[i].id);
    printf("\n");
    for(int i=0; i<g.edges_number; i++)
        printf("%d\n", g.edges[i].weight);

    return 0;
}
