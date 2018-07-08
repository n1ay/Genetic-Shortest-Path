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

    Population population1;
    population1.genome_length=8;
    int crossover_index=randombytes_uniform((const uint32_t) population1.genome_length);

    Individual individual1, individual2;
    individual1.population = &population1;
    individual2.population = &population1;
    int genome1[] = {1,2,3,4,5,6,7,8};
    int genome2[] = {9,10,11,12,13,14,15,16};
    individual1.genome = genome1;
    individual2.genome = genome2;

    Individual* children = reproduce(individual1, individual2, crossover_index);
    for(int i=0; i<crossover_index; i++) {
        ASSERT_EQUALS(children[1].genome[i], genome2[i]);
        ASSERT_EQUALS(children[0].genome[i], genome1[i]);
    }
    for(int i=crossover_index; i<population1.genome_length; i++) {
        ASSERT_EQUALS(children[0].genome[i], genome2[i]);
        ASSERT_EQUALS(children[1].genome[i], genome1[i]);
    }
}

void test_mutate(void) {
    Population population1;
    population1.genome_length=8;

    Individual individual1, individual2;
    individual1.population = &population1;
    individual2.population = &population1;

    int genome1[] = {1,2,3,4,5,6,7,8};
    int genome2[] = {1,2,3,4,5,6,7,8};
    individual1.genome = genome1;
    individual2.genome = genome2;

    int mutated_gene = mutate(&individual1);

    ASSERT_NOT_EQUALS(individual1.genome[mutated_gene], (individual2.genome[mutated_gene]));
    for(int i=0; i<population1.genome_length; i++) {
        if(i!=mutated_gene)
            ASSERT_EQUALS(individual1.genome[i], individual2.genome[i]);
    }
}

void test_get_fitness(void) {
    ASSERT_FAIL
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
    TEST(test_get_fitness);
}

#pragma clang diagnostic pop