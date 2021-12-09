#ifndef ADVENTOFCODE_2021_COMMON_H
#define ADVENTOFCODE_2021_COMMON_H

#include <vector>
#include <string>
#include <cassert>
#include <ranges>

template<typename T>
std::vector<T> split(const std::string &line, const std::string &c) {
    auto view = line | std::ranges::views::split(c) |
                std::ranges::views::transform([](auto &&str) { return (T) std::strtol(&*str.begin(), nullptr, 10); }) |
                std::ranges::views::common;
    return {view.begin(), view.end()};
}

template<typename T>
std::pair<T, T> vector_to_pair(const std::vector<T> &v) {
    assert(v.size() == 2);
    return {v[0], v[1]};
}

template<typename T = std::string_view>
std::vector<T> split(const std::string_view &line, const std::string &c) {
    auto view = line | std::ranges::views::split(c) |
                std::ranges::views::transform(
                        [](auto &&str) { return std::string_view(&*str.begin(), std::ranges::distance(str)); }) |
                std::ranges::views::common;
    if constexpr (std::is_same_v<T, std::string_view>)
        return {view.begin(), view.end()};
    std::vector<T> res;
    for (auto &&v: view)
        res.emplace_back(T(v.begin(), v.end()));
    return res;
}

std::vector<std::string_view> split(const std::string &line, const std::string &c) {
    return split(std::string_view(line), c);
}

#endif //ADVENTOFCODE_2021_COMMON_H
