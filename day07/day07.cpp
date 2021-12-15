#include "day07.h"

#include <algorithm>

#include "../common.h"

day07::input_t day07::parse(const parse_t &input) {
    input_t res;
    for (auto &&line: input)
        for (auto &&s: split_str(line, ","))
            res.push_back(std::strtol(&*s.begin(), nullptr, 10));
    return res;
}

day07::output_t day07::first_part(const day07::input_t &input) {
    auto cache = input;
    std::sort(cache.begin(), cache.end());
    auto amount = cache[cache.size() / 2];
    auto res = 0;
    for (auto &&c: cache)
        res += std::abs(c - amount);
    return res;
}

auto count(auto &&input, auto f) {
    auto res = 0;
    for (auto &&i: input) {
        auto num = i - f > 0 ? i - f : f - i;
        res += num * (num + 1);
    }
    return res >> 1;
}

day07::output_t day07::second_part(const day07::input_t &input) {
    auto low = 0;
    for (auto &&i: input)
        low += i;
    low = low / (int) input.size();
    return std::min(count(input, low), count(input, low + 1));

    int32_t a;
    int b;
}

day07::output_t day07::expected_p1() {
    return 342641;
}

day07::output_t day07::expected_p2() {
    return 93006301;
}
