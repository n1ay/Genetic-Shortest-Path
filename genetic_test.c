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

    population population1;
    population1.genome_length=8;
    int crossover_index=randombytes_uniform((const uint32_t) population1.genome_length);

    individual individual1, individual2;
    individual1.population = &population1;
    individual2.population = &population1;
    int genome1[] = {1,2,3,4,5,6,7,8};
    int genome2[] = {9,10,11,12,13,14,15,16};
    individual1.genome = genome1;
    individual2.genome = genome2;

    individual* childs = reproduce(individual1, individual2, crossover_index);
    for(int i=0; i<crossover_index; i++) {
        ASSERT_EQUALS(childs[1].genome[i], genome2[i]);
        ASSERT_EQUALS(childs[0].genome[i], genome1[i]);
    }
    for(int i=crossover_index; i<population1.genome_length; i++) {
        ASSERT_EQUALS(childs[0].genome[i], genome2[i]);
        ASSERT_EQUALS(childs[1].genome[i], genome1[i]);
    }
}

void test(void) {
    TEST(test_reproduce);
}

#pragma clang diagnostic pop