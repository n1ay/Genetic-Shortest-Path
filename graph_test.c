//
// Created by kamil on 08.07.18.
//

#include "graph_test.h"
#include "unittest.h"
#include "graph.h"

void test_get_all_weights_sum(void) {
    Graph graph = build_exemplary_graph();
    ASSERT_EQUALS(get_all_weights_sum(graph), 15);
    delete_graph(graph);
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

    delete_graph(graph);
    free(edges);
    free(edges_fake);
    free(edges_reversed);
    free(vertices);
}

void test_build_exemplary_graph(void) {
    int vertices_number = 7;
    int edges_number = 8;
    Graph graph = build_exemplary_graph();
    ASSERT_EQUALS(graph.vertices_number, vertices_number);
    ASSERT_EQUALS(graph.edges_number, edges_number);
    ASSERT_EQUALS(graph.edges[0].from->id, graph.vertices[0].id);
    ASSERT_EQUALS(graph.edges[0].to->id, graph.vertices[1].id);
    ASSERT_EQUALS(graph.edges[1].from->id, graph.vertices[0].id);
    ASSERT_EQUALS(graph.edges[1].to->id, graph.vertices[2].id);
    ASSERT_EQUALS(graph.edges[2].from->id, graph.vertices[1].id);
    ASSERT_EQUALS(graph.edges[2].to->id, graph.vertices[3].id);
    ASSERT_EQUALS(graph.edges[3].from->id, graph.vertices[2].id);
    ASSERT_EQUALS(graph.edges[3].to->id, graph.vertices[3].id);
    ASSERT_EQUALS(graph.edges[4].from->id, graph.vertices[3].id);
    ASSERT_EQUALS(graph.edges[4].to->id, graph.vertices[4].id);
    ASSERT_EQUALS(graph.edges[5].from->id, graph.vertices[3].id);
    ASSERT_EQUALS(graph.edges[5].to->id, graph.vertices[5].id);
    ASSERT_EQUALS(graph.edges[6].from->id, graph.vertices[4].id);
    ASSERT_EQUALS(graph.edges[6].to->id, graph.vertices[6].id);
    ASSERT_EQUALS(graph.edges[7].from->id, graph.vertices[5].id);
    ASSERT_EQUALS(graph.edges[7].to->id, graph.vertices[6].id);

    delete_graph(graph);
}

void graph_test(void) {
    TEST(test_get_all_weights_sum);
    TEST(test_get_edge_weight);
    TEST(test_build_exemplary_graph);
}
