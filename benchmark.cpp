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

template<std::invocable Func>
auto time(Func && f) {
    auto t1 = std::chrono::high_resolution_clock::now();
    auto res = f();
    auto t2 = std::chrono::high_resolution_clock::now();
    return std::make_pair(res, std::chrono::duration<double, std::chrono::milliseconds::period>(t2 - t1).count());
}

auto total = 0.0;

#define BENCHMARK(day) { \
    auto filename = std::string("input/") + #day + ".txt"; \
    std::ifstream file(filename);                \
    parse_t input{};       \
    std::string line;      \
    while (std::getline(file, line))                     \
        input.push_back(line);                             \
    auto parsing = time([&](){return day::parse(input);}); \
    auto first_part = time([&](){return day::first_part(parsing.first);}); \
    assert(first_part.first == day::expected_p1());\
    auto second_part = time([&](){return day::second_part(parsing.first);});\
    assert(second_part.first == day::expected_p2());\
    std::cout << std::format("{} {:^8.4f} {:^8.4f} {:^8.4f} {:^8.4f}\n", #day, parsing.second, first_part.second, second_part.second, parsing.second + first_part.second + second_part.second); \
    total += parsing.second + first_part.second + second_part.second;\
}

int main() {
    std::cout << std::format("{:<5} {:^8} {:^8} {:^8} {:^8}   ms\n", "Day", "Parsing", "Part 1", "Part 2", "Sum");

    BENCHMARK(day01)
    BENCHMARK(day02)
    BENCHMARK(day03)
    BENCHMARK(day04)
    BENCHMARK(day05)
    BENCHMARK(day06)
    BENCHMARK(day07)
    BENCHMARK(day08)
    BENCHMARK(day09)
    BENCHMARK(day10)
    BENCHMARK(day11)
    BENCHMARK(day12)
    BENCHMARK(day13)

    std::cout << "Total: " << total << "ms\n";
}
