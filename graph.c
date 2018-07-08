//
// Created by kamil on 08.07.18.
//

#include <stdlib.h>
#include "graph.h"

Graph build_exemplary_graph() {
    Graph g;
    g.bidirectional = 1;
    g.vertices_number = 7;
    g.edges_number = 8;

    g.vertices = malloc(g.vertices_number*sizeof(Vertex));
    g.edges = malloc(g.edges_number*sizeof(Edge));

    for(int i=0; i<g.vertices_number; i++) {
        Vertex v;
        v.id = i;
        g.vertices[i] = v;
    }

    int id[] = {0, 1, 2, 3, 4, 5, 6, 7};
    Vertex* from[] = {&g.vertices[0], &g.vertices[0], &g.vertices[1], &g.vertices[2],
                      &g.vertices[3], &g.vertices[3], &g.vertices[4], &g.vertices[5]};

    Vertex* to[] = {&g.vertices[1], &g.vertices[2], &g.vertices[3], &g.vertices[3],
                    &g.vertices[4], &g.vertices[5], &g.vertices[6], &g.vertices[6]};

    int weights[] = {2, 1, 2, 2, 2, 3, 1, 2};
    for(int i=0; i<g.edges_number; i++) {
        Edge e;
        e.id = id[i];
        e.from = from[i];
        e.to = to[i];
        e.weight = weights[i];
        g.edges[i] = e;
    }

    return g;
}

int get_all_weights_sum(const Graph graph) {
    int sum = 0;
    for(int i=0; i<graph.edges_number; i++) {
        sum+=graph.edges[i].weight;
    }
    return sum;
}

int edge_exists(const Edge edge, const Graph graph) {
    if (graph.bidirectional) {
        for (int i = 0; i < graph.edges_number; i++) {
            if ((graph.edges[i].from->id == edge.from->id &&
                 graph.edges[i].to->id == edge.to->id)
                ||
                (graph.edges[i].from->id == edge.to->id &&
                 graph.edges[i].to->id == edge.from->id))
                return 1;
        }
    } else {
        for (int i = 0; i < graph.edges_number; i++) {
            if (graph.edges[i].from->id == edge.from->id &&
                graph.edges[i].to->id == edge.to->id)
                return 1;
        }
    }
    return 0;
}