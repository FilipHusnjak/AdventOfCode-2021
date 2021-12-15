#ifndef ADVENTOFCODE_2021_COMMON_H
#define ADVENTOFCODE_2021_COMMON_H

#include <vector>
#include <string>
#include <cassert>
#include <ranges>

template<typename T>
std::pair<T, T> vector_to_pair(const std::vector<T> &v) {
    assert(v.size() == 2);
    return {v[0], v[1]};
}

std::vector<int> split_int(const std::string_view &line, const std::string &c);

std::vector<int> split_int(const std::string &line, const std::string &c);

std::vector<int> split_int(const std::string &line);

template<typename T = std::string_view>
std::vector<T> split_str(const std::string_view &line, const std::string &c) {
    auto view = line | std::ranges::views::split(c) |
                std::ranges::views::transform(
                        [](auto &&str) { return std::string_view(&*str.begin(), std::ranges::distance(str)); }) |
                std::ranges::views::common;
    if constexpr (std::is_same<T, std::string_view>::value)
        return {view.begin(), view.end()};

    std::vector<T> res;
    for (auto &&v: view) {
        if constexpr (std::constructible_from<T, decltype(v)>)
            res.emplace_back(v);
        else res.push_back(T(v.begin(), v.end()));
    }
    return res;
}

template<typename T = std::string_view>
std::vector<T> split_str(const std::string &line, const std::string &c) {
    return split_str<T>(std::string_view(line), c);
}

#endif //ADVENTOFCODE_2021_COMMON_H
