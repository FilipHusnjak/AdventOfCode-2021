#include "day06.h"

#include "../common.h"

day06::input_t day06::parse(const parse_t &input) {
    input_t states{};
    for (auto &&i: input) {
        auto nums = split_int(i, ",");
        for (auto num: nums)
            states[num]++;
    }
    return states;
}

template<size_t N>
auto solve(auto states) {
    for (int i = 0; i < N; i++) {
        auto next = states[0];
        for (int j = 0; j < 8; j++)
            states[j] = states[j + 1];
        states[6] += next;
        states[8] = next;
    }
    long long res = 0;
    for (auto &&s: states)
        res += s;
    return res;
}

day06::output_t day06::first_part(const day06::input_t &input) {
    return solve<80>(input);
}

day06::output_t day06::second_part(const day06::input_t &input) {
    return solve<256>(input);
}

day06::output_t day06::expected_p1() {
    return 379414;
}

day06::output_t day06::expected_p2() {
    return 1705008653296;
}
