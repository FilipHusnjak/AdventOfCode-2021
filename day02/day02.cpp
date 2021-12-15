#include "day02.h"

#include <algorithm>

#include "../common.h"

auto &operator+=(std::pair<int, int> &left, const std::pair<int, int> &right) {
    left.first += right.first;
    left.second += right.second;
    return left;
}

day02::input_t day02::parse(const parse_t &input) {
    input_t res(input.size());
    std::ranges::transform(input, res.begin(), [](auto &&str) {
        auto &&v = split_str(str, " ");
        int amount = std::strtol(&*v[1].begin(), nullptr, 10);
        if (str[0] == 'f') return std::make_pair(amount, 0);
        else if (str[0] == 'd') return std::make_pair(0, amount);
        return std::make_pair(0, -amount);
    });
    return res;
}

day02::output_t day02::first_part(const day02::input_t &input) {
    std::pair<int, int> result;
    for (const auto &i: input)
        result += i;
    return result.first * result.second;
}

day02::output_t day02::second_part(const day02::input_t &input) {
    std::pair<int, int> result;
    for (long aim = 0; const auto &i: input)
        result += {i.first, (aim += i.second) * i.first};
    return result.first * result.second;
}

day02::output_t day02::expected_p1() {
    return 1804520;
}

day02::output_t day02::expected_p2() {
    return 1971095320;
}
