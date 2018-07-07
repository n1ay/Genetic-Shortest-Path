#include <stdio.h>
#include <stdlib.h>
#include <sodium.h>
#include "graph.h"
#include "genetic_test.h"

graph build_graph() {
    graph g;
    int vertices = 7;
    int edges = 8;

    g.vertices = malloc(vertices*sizeof(vertex));
    g.edges = malloc(edges* sizeof(edge));

    for(int i=0; i<vertices; i++) {
        vertex v;
        v.id = i;
        g.vertices[i] = v;
    }

    int id[] = {0, 1, 2, 3, 4, 5, 6, 7};
    vertex* from[] = {&g.vertices[0], &g.vertices[0], &g.vertices[1], &g.vertices[2],
                      &g.vertices[3], &g.vertices[3], &g.vertices[4], &g.vertices[5]};

    vertex* to[] = {&g.vertices[1], &g.vertices[2], &g.vertices[3], &g.vertices[3],
                      &g.vertices[4], &g.vertices[5], &g.vertices[6], &g.vertices[6]};

    int weights[] = {2, 1, 2, 2, 2, 3, 1, 2};
    for(int i=0; i<edges; i++) {
        edge e;
        e.id = id[i];
        e.from = from[i];
        e.to = to[i];
        e.weight = weights[i];
        g.edges[i] = e;
    }

    return g;
}

#define PERFORM_TESTS 1

int main() {
    sodium_init();

    if(PERFORM_TESTS == 1)
        test();

    graph g = build_graph();
    int vertices = 7;
    int edges = 8;

    for(int i=0; i<vertices; i++)
        printf("%d\n", g.vertices[i].id);
    printf("\n");
    for(int i=0; i<edges; i++)
        printf("%d\n", g.edges[i].weight);

    return 0;
}
