#include "common.h"

std::vector<int> split_int(const std::string_view &line, const std::string &c) {
    auto view = line | std::ranges::views::split(c) |
                std::ranges::views::transform([](auto &&str) { return std::strtol(&*str.begin(), nullptr, 10); }) |
                std::ranges::views::common;
    return {view.begin(), view.end()};
}

std::vector<int> split_int(const std::string &line, const std::string &c) {
    auto view = line | std::ranges::views::split(c) |
                std::ranges::views::transform([](auto &&str) { return std::strtol(&*str.begin(), nullptr, 10); }) |
                std::ranges::views::common;
    return {view.begin(), view.end()};
}

std::vector<int> split_int(const std::string &line) {
    std::vector<int> res;
    for (char *ptr_begin = const_cast<char *>(&*line.begin()); ptr_begin <= &*line.rbegin(); ptr_begin++) {
        if (std::isspace(*ptr_begin)) continue;
        res.push_back(std::strtol(ptr_begin, &ptr_begin, 10));
    }
    return res;
}
