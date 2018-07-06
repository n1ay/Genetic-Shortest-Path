cmake_minimum_required(VERSION 3.5)
project(Genetic C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic -pedantic-errors")
set(CMAKE_C_STANDARD 99)

add_executable(Genetic main.c graph.h)
