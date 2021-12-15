#include "day14.h"

#include "../common.h"

namespace std {
    template<>
    struct hash<std::pair<char, char>> {
        size_t operator()(auto &&p) const {
            return ((size_t) p.first << 32) + (size_t) p.second;
        }
    };
}

day14::input_t day14::parse(const parse_t &input) {
    input_t res;
    for (int i = 0; i < input[0].size() - 1; i++) {
        res.first.first[{input[0][i], input[0][i + 1]}].first++;
        res.first.second[input[0][i]]++;
    }
    res.first.second[input[0][input[0].size() - 1]]++;
    for (int i = 2; i < input.size(); i++) {
        auto &&v = split_str(input[i], " -> ");
        std::pair c = {v[0][0], v[0][1]};
        res.second[c] = v[1][0];
    }
    return res;
}

template<auto N>
day14::output_t solve(const day14::input_t &input) {
    auto polymer_pairs = input.first.first;
    auto char_cnts = input.first.second;
    for (int i = 0; i < N; i++) {
        for (auto &&[k, v]: polymer_pairs) {
            if (!input.second.contains(k)) continue;
            auto &&c = input.second.at(k);
            char_cnts[c] += v.first;
            polymer_pairs[{k.first, c}].second += v.first;
            polymer_pairs[{c, k.second}].second += v.first;
            v.first = 0;
        }
        for (auto &&[k, v]: polymer_pairs) {
            v.first += v.second;
            v.second = 0;
        }
    }
    long long max_v = 0, min_v = std::numeric_limits<long long>::max();
    for (auto &&[k, v]: char_cnts) {
        max_v = std::max(max_v, v);
        min_v = std::min(min_v, v);
    }
    return max_v - min_v;
}

day14::output_t day14::first_part(const day14::input_t &input) {
    return solve<10>(input);
}

day14::output_t day14::second_part(const day14::input_t &input) {
    return solve<40>(input);
}

day14::output_t day14::expected_p1() {
    return 2194LL;
}

day14::output_t day14::expected_p2() {
    return 2360298895777LL;
}
