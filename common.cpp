#include "common.h"

#include <ranges>

std::vector<int> split(const std::string &line, char c) {
    auto view = line | std::ranges::views::split(c) |
                std::ranges::views::transform([](auto &&str) { return std::strtol(&*str.begin(), nullptr, 10); }) |
                std::ranges::views::common;
    return {view.begin(), view.end()};
}
