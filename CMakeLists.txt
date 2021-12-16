cmake_minimum_required(VERSION 3.20)
project(AdventOfCode_2021)

set(CMAKE_CXX_STANDARD 23)

add_executable(benchmark benchmark.cpp common.cpp
        day01/day01.cpp
        day02/day02.cpp
        day03/day03.cpp
        day04/day04.cpp
        day05/day05.cpp
        day06/day06.cpp
        day07/day07.cpp
        day08/day08.cpp
        day09/day09.cpp
        day10/day10.cpp
        day11/day11.cpp
        day12/day12.cpp
        day13/day13.cpp
        day14/day14.cpp
        day15/day15.cpp
        day16/day16.cpp)
