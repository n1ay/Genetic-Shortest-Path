cmake_minimum_required(VERSION 3.5)
project(Genetic C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -pedantic-errors -Wno-unknown-pragmas")
set(CMAKE_C_STANDARD 99)

add_library(sodium_random main.c genetic.c)
target_link_libraries(sodium_random -lsodium)

add_executable(Genetic main.c graph.h genetic.c genetic.h
    genetic_test.c genetic_test.h unittest.h)

target_link_libraries(Genetic sodium_random)
