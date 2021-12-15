#include "day03.h"

#include <cmath>
#include <list>
#include <functional>

day03::input_t day03::parse(const parse_t &input) {
    return input;
}

day03::output_t day03::first_part(const day03::input_t &input) {
    std::vector<int> counts(input[0].size(), 0);
    for (const auto &i: input)
        for (int j = 0; j < i.size(); j++)
            counts[j] += i[j] == '1';
    long res = 0;
    for (size_t half = input.size() >> 1; int count: counts)
        res = (res + (count > half)) << 1;
    res >>= 1;
    return res * (res ^ ((int) std::pow(2.0, (double) counts.size()) - 1));
}

auto get_rating(const std::vector<std::string> &input, const std::function<bool(int, int)> &f) {
    if (input.empty()) return 0;
    std::list<std::string> result(input.begin(), input.end());
    for (int bit = 0; result.size() > 1 && bit < input[0].size(); bit++) {
        int count = 0;
        for (const auto &r: result)
            count += r[bit] == '0';
        char c = f(count, (int) result.size() / 2) ? '1' : '0';
        for (auto it = result.begin(); it != result.end();) {
            if ((*it)[bit] != c) it = result.erase(it);
            else it++;
        }
    }
    if (result.empty()) return 0;
    return (int) std::stol(*result.begin(), nullptr, 2);
}

day03::output_t day03::second_part(const day03::input_t &input) {
    return get_rating(input, std::less_equal<>()) * get_rating(input, std::greater<>());
}

day03::output_t day03::expected_p1() {
    return 2967914;
}

day03::output_t day03::expected_p2() {
    return 7041258;
}
