#ifndef ADVENTOFCODE_2021_COMMON_H
#define ADVENTOFCODE_2021_COMMON_H

#include <vector>
#include <string>
#include <cassert>
#include <ranges>

template<typename T>
std::vector<T> split(const std::string &line, const std::string &c) {
    auto view = line | std::ranges::views::split(c) |
                std::ranges::views::transform([](auto &&str) { return (T)std::strtol(&*str.begin(), nullptr, 10); }) |
                std::ranges::views::common;
    return {view.begin(), view.end()};
}

template<typename T>
std::pair<T, T> vector_to_pair(const std::vector<T> &v) {
    assert(v.size() == 2);
    return {v[0], v[1]};
}

#endif //ADVENTOFCODE_2021_COMMON_H
