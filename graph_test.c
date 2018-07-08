//
// Created by kamil on 08.07.18.
//

#include "graph_test.h"
#include "unittest.h"
#include "graph.h"

void test_get_all_weights_sum(void) {
    Graph graph = build_exemplary_graph();
    ASSERT_EQUALS(get_all_weights_sum(graph), 15);
}

void test_get_edge_weight(void) {
    Graph graph = build_exemplary_graph();
    Vertex* vertices = malloc(graph.vertices_number*sizeof(Vertex));
    Edge* edges = malloc(graph.edges_number*sizeof(Edge));
    Edge* edges_reversed = malloc(graph.edges_number*sizeof(Edge));
    Edge* edges_fake = malloc(graph.edges_number*sizeof(Edge));

    for(int i=0; i<graph.vertices_number; i++) {
        vertices[i] = create_vertex(i);
    }

    Vertex* from[] = {&vertices[0], &vertices[0], &vertices[1], &vertices[2],
                      &vertices[3], &vertices[3], &vertices[4], &vertices[5]};

    Vertex* to[] = {&vertices[1], &vertices[2], &vertices[3], &vertices[3],
                    &vertices[4], &vertices[5], &vertices[6], &vertices[6]};


    Vertex* from_fake[] = {&vertices[0], &vertices[0], &vertices[1], &vertices[2],
                           &vertices[3], &vertices[0], &vertices[4], &vertices[5]};

    Vertex* to_fake[] = {&vertices[3], &vertices[5], &vertices[4], &vertices[6],
                         &vertices[6], &vertices[6], &vertices[0], &vertices[2]};

    for(int i=0; i<graph.edges_number; i++) {
        edges[i] = create_edge(0, 0, from[i], to[i]);
        edges_fake[i] = create_edge(0, 0, from_fake[i], to_fake[i]);
        edges_reversed[i] = create_edge(0, 0, to[i], from[i]);
    }

    for(int i=0; i<graph.edges_number; i++) {
        ASSERT_GREATER_EQUALS(get_edge_weight(edges[i], graph), 1);
        ASSERT_GREATER_EQUALS(get_edge_weight(edges_reversed[i], graph), 1);
        ASSERT_EQUALS(get_edge_weight(edges_fake[i], graph), -1);
    }
    graph.bidirectional = 0;
    for(int i=0; i<graph.edges_number; i++) {
        ASSERT_GREATER_EQUALS(get_edge_weight(edges[i], graph), 1);
        ASSERT_EQUALS(get_edge_weight(edges_reversed[i], graph), -1);
        ASSERT_EQUALS(get_edge_weight(edges_fake[i], graph), -1);
    }
}

void graph_test(void) {
    TEST(test_get_all_weights_sum);
    TEST(test_get_edge_weight);
}
