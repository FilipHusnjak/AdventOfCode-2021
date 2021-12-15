#include "day01.h"

#include <algorithm>

#include "../benchmark.h"

day01::input_t day01::parse(const parse_t &input) {
    input_t res(input.size());
    std::ranges::transform(input, res.begin(), [](auto &&str) { return std::stoi(str); });
    return res;
}

day01::output_t day01::first_part(const day01::input_t &input) {
    int count = 0;
    for (int i = 1; i < input.size(); i++)
        count += input[i] > input[i - 1];
    return count;
}

day01::output_t day01::second_part(const day01::input_t &input) {
    int count = 0;
    for (int i = 3; i < input.size(); i++)
        count += input[i] > input[i - 3];
    return count;
}

day01::output_t day01::expected_p1() {
    return 1527;
}

day01::output_t day01::expected_p2() {
    return 1575;
}
