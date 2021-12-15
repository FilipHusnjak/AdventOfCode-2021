#include "benchmark.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>

#include "day01/day01.h"
#include "day02/day02.h"
#include "day03/day03.h"
#include "day04/day04.h"
#include "day05/day05.h"
#include "day06/day06.h"
#include "day07/day07.h"
#include "day08/day08.h"
#include "day09/day09.h"
#include "day10/day10.h"
#include "day11/day11.h"
#include "day12/day12.h"
#include "day13/day13.h"
#include "day14/day14.h"
#include "day15/day15.h"

#define NUM_ITER 1

template<std::invocable Func>
auto time(Func && f) {
    auto t1 = std::chrono::high_resolution_clock::now();
    f();
    auto t2 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::chrono::milliseconds::period>(t2 - t1).count();
}

auto total = 0.0;

#define BENCHMARK(day, num_iter) { \
    auto filename = std::string("input/") + #day + ".txt"; \
    std::ifstream file(filename);                \
    parse_t input{};       \
    std::string line;      \
    while (std::getline(file, line))                     \
        input.push_back(line);                             \
    auto parsing_time = time([&](){return day::parse(input);});    \
    for (int i = 0; i < (num_iter) - 1; i++)    \
        parsing_time += time([&](){return day::parse(input);});    \
    parsing_time /= (num_iter);\
    auto parsing_res = day::parse(input);\
    auto first_time = time([&](){return day::first_part(parsing_res);}); \
    for (int i = 0; i < (num_iter) - 1; i++)                           \
        first_time += time([&](){return day::first_part(parsing_res);}); \
    first_time /= (num_iter);  \
    auto first_res = day::first_part(parsing_res);\
    assert(first_res == day::expected_p1());\
    auto second_time = time([&](){return day::second_part(parsing_res);}); \
    for (int i = 0; i < (num_iter) - 1; i++)                           \
        second_time += time([&](){return day::second_part(parsing_res);}); \
    second_time /= (num_iter);     \
    auto second_res = day::second_part(parsing_res);\
    assert(second_res == day::expected_p2());\
    std::cout << std::format("| {} | {:^8.4f} | {:^8.4f} | {:^8.4f} | {:^8.4f} |\n", #day, parsing_time, first_time, second_time, parsing_time + first_time + second_time); \
    total += parsing_time + first_time + second_time;\
}

int main() {
    std::cout
            << std::format("| {:<5} | {:^8} | {:^8} | {:^8} | {:^8} |\n", "day", "parsing", "part_1", "part_2", "sum");

    BENCHMARK(day01, NUM_ITER)
    BENCHMARK(day02, NUM_ITER)
    BENCHMARK(day03, NUM_ITER)
    BENCHMARK(day04, NUM_ITER)
    BENCHMARK(day05, NUM_ITER)
    BENCHMARK(day06, NUM_ITER)
    BENCHMARK(day07, NUM_ITER)
    BENCHMARK(day08, NUM_ITER)
    BENCHMARK(day09, NUM_ITER)
    BENCHMARK(day10, NUM_ITER)
    BENCHMARK(day11, NUM_ITER)
    BENCHMARK(day12, NUM_ITER)
    BENCHMARK(day13, NUM_ITER)
    BENCHMARK(day14, NUM_ITER)
    BENCHMARK(day15, NUM_ITER)

    std::cout << "Total: " << total << "ms\n";
}
