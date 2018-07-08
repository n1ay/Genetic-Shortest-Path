//
// Created by kamil on 06.07.18.
//

#ifndef GENETIC_GRAPH_H
#define GENETIC_GRAPH_H

typedef struct {
    int id;
} Vertex;

typedef struct {
    int id;
    Vertex* from;
    Vertex* to;
    int weight;
} Edge;

typedef struct {
    int id_from;
    int id_to;
} Path;

typedef struct {
    Vertex* vertices;
    int vertices_number;

    Edge* edges;
    int edges_number;

    int bidirectional;
    Path path;
} Graph;

Vertex create_vertex(int id);
Edge create_edge(int id, int weight, Vertex* from, Vertex* to);
Graph build_exemplary_graph();
int get_all_weights_sum(Graph graph);
int get_edge_weight(Edge edge, Graph graph);
#endif //GENETIC_GRAPH_H
