//
// Created by kamil on 06.07.18.
//

#ifndef GENETIC_GRAPH_H
#define GENETIC_GRAPH_H

typedef struct {
    int id;
} vertex;

typedef struct {
    int id;
    vertex* from;
    vertex* to;
    int weight;
} edge;

typedef struct {
    vertex* vertices;
    edge* edges;
} graph;

#endif //GENETIC_GRAPH_H
