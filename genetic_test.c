//
// Created by kamil on 07.07.18.
//

#include "genetic_test.h"
#include "unittest.h"

#include <stdlib.h>
#include <stdio.h>
#include "genetic.h"
#include <sodium.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-stack-address"

void test_reproduce(void) {

    Population population;
    population.genome_length=8;
    int crossover_index=randombytes_uniform((const uint32_t) population.genome_length);

    int genome1[] = {1,2,3,4,5,6,7,8};
    int genome2[] = {9,10,11,12,13,14,15,16};
    Individual individual1 = create_individual(genome1, &population), individual2 = create_individual(genome2, &population);

    Individual* children = reproduce(individual1, individual2, crossover_index);
    for(int i=0; i<crossover_index; i++) {
        ASSERT_EQUALS(children[1].genome[i], genome2[i]);
        ASSERT_EQUALS(children[0].genome[i], genome1[i]);
    }
    for(int i=crossover_index; i<population.genome_length; i++) {
        ASSERT_EQUALS(children[0].genome[i], genome2[i]);
        ASSERT_EQUALS(children[1].genome[i], genome1[i]);
    }
    free(children[0].genome);
    free(children[1].genome);
    free(children);
}

void test_mutate(void) {
    Population population;
    population.genome_length=8;

    int genome1[] = {1,2,3,4,5,6,7,8};
    int genome2[] = {1,2,3,4,5,6,7,8};

    Individual individual1 = create_individual(genome1, &population), individual2 = create_individual(genome2, &population);

    int mutated_gene = mutate(&individual1);

    ASSERT_NOT_EQUALS(individual1.genome[mutated_gene], (individual2.genome[mutated_gene]));
    for(int i=0; i<population.genome_length; i++) {
        if(i!=mutated_gene)
            ASSERT_EQUALS(individual1.genome[i], individual2.genome[i]);
    }
}

void test_get_fitness(void) {
    Graph graph = build_exemplary_graph();
    Population population;
    population.genome_length=7;
    population.graph = &graph;

    int genome1[] = {3,2,3,4,6,0,0};
    Individual individual1 = create_individual(genome1, &population);
    ASSERT_EQUALS(get_fitness(individual1), 1.0/(8+9*15*10));

    int genome2[] = {0,2,3,4,6,-10,-20};
    Individual individual2 = create_individual(genome2, &population);
    ASSERT_EQUALS(get_fitness(individual2), 1.0/7);

    int genome3[] = {0,1,3,4,3,5,6};
    Individual individual3 = create_individual(genome3, &population);
    ASSERT_EQUALS(get_fitness(individual3), 1.0/14);

    int genome4[] = {0,1,3,4,3,5,3};
    Individual individual4 = create_individual(genome4, &population);
    ASSERT_EQUALS(get_fitness(individual4), 1.0/(15+7*15*10));

    int genome5[] = {0,0,0,0,0,0,0};
    Individual individual5 = create_individual(genome5, &population);
    ASSERT_EQUALS(get_fitness(individual5), 1.0/(1+6*15*10+7*15*10));

    int genome6[] = {1,1,1,1,1,1,1};
    Individual individual6 = create_individual(genome6, &population);
    ASSERT_EQUALS(get_fitness(individual6), 1.0/(1+6*15*10+2*7*15*10));

    delete_graph(graph);
}

void test_reproduce_apply_genetic_operators(void) {
    Population population;
    population.genome_length=8;
    population.mutation_rate=0;
    population.crossover_rate=0;

    int genome1[] = {1,2,3,4,5,6,7,8};
    int genome2[] = {9,10,11,12,13,14,15,16};
    Individual individual1 = create_individual(genome1, &population), individual2 = create_individual(genome2, &population);

    Individual* children = reproduce_apply_genetic_operators(individual1, individual2);
    for(int i=0; i<population.genome_length; i++) {
        ASSERT_EQUALS(children[0].genome[i], genome2[i]);
        ASSERT_EQUALS(children[1].genome[i], genome1[i]);
    }
    free(children[0].genome);
    free(children[1].genome);
    free(children);
}

//just in case
void test_unittest(void) {
    ASSERT_EQUALS(1+1, 2);
    ASSERT_GREATER(0, -2);
    ASSERT_GREATER_EQUALS(0, -2);
    ASSERT_GREATER_EQUALS(-2, -2);
    ASSERT_LESS(0, 2);
    ASSERT_LESS_EQUALS(0, 2);
    ASSERT_LESS_EQUALS(-2, -2);
    ASSERT_NOT_EQUALS(-2, 2);
}

void genetic_test(void) {
    TEST(test_unittest);
    TEST(test_reproduce);
    TEST(test_mutate);
    TEST(test_reproduce_apply_genetic_operators);
    TEST(test_get_fitness);
}

#pragma clang diagnostic pop