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

void test_edge_exists(void) {
    Graph graph = build_exemplary_graph();
    Vertex* vertices = malloc(graph.vertices_number*sizeof(Vertex));
    Edge* edges = malloc(graph.edges_number*sizeof(Edge));
    Edge* edges_reversed = malloc(graph.edges_number*sizeof(Edge));
    Edge* edges_fake = malloc(graph.edges_number*sizeof(Edge));

    for(int i=0; i<graph.vertices_number; i++) {
        Vertex v;
        v.id = i;
        vertices[i] = v;
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
        Edge e, e_fake, e_reversed;
        e.from = from[i];
        e.to = to[i];
        edges[i] = e;

        e_fake.from = from_fake[i];
        e_fake.to = to_fake[i];
        edges_fake[i] = e_fake;

        e_reversed.from = to[i];
        e_reversed.to = from[i];
        edges_reversed[i] = e_reversed;
    }

    for(int i=0; i<graph.edges_number; i++) {
        ASSERT_EQUALS(edge_exists(edges[i], graph), 1);
        ASSERT_EQUALS(edge_exists(edges_reversed[i], graph), 1);
        ASSERT_EQUALS(edge_exists(edges_fake[i], graph), 0);
    }
    graph.bidirectional = 0;
    for(int i=0; i<graph.edges_number; i++) {
        ASSERT_EQUALS(edge_exists(edges[i], graph), 1);
        ASSERT_EQUALS(edge_exists(edges_reversed[i], graph), 0);
        ASSERT_EQUALS(edge_exists(edges_fake[i], graph), 0);
    }
}

void graph_test(void) {
    TEST(test_get_all_weights_sum);
    TEST(test_edge_exists);
}
