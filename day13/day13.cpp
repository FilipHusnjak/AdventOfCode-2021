#include "day13.h"

#include <algorithm>

#include "../common.h"

day13::input_t day13::parse(const parse_t &input) {
    input_t res;
    int i;
    for (i = 0; i < input.size() && !input[i].empty() && !std::isspace(input[i][0]); i++)
        res.first.insert(vector_to_pair(split_int(input[i], ",")));
    for (i++; i < input.size(); i++) {
        auto &&v = split_str(split_str(input[i], " ")[2], "=");
        auto num = std::strtol(&*v[1].begin(), nullptr, 10);
        if (v[0] == "x")
            res.second.first.push_back(num);
        else
            res.second.second.push_back(num);
    }
    return res;
}

template<auto First>
auto iterate(std::set<day13::point, day13::comp> &points, auto &&points_out, auto &&moves) {
    std::vector<int> accumulated;
    auto it = points.begin();
    int init = (int) moves.size() - 1;
    if constexpr (First) init = 0;
    for (int i = init; i >= 0; i--) {
        while (it != points.end() && it->first > moves[i]) {
            points.emplace(2 * moves[i] - it->first, it->second);
            it = points.erase(it);
        }
    }
    for (auto &&p: points)
        points_out.emplace(p.second, p.first);
}

template<auto First>
auto solve(auto points, auto moves_x, auto moves_y) {
    if constexpr (!First) {
        std::sort(moves_x.begin(), moves_x.end());
        std::sort(moves_y.begin(), moves_y.end());
    }
    std::set<day13::point, day13::comp> points_second;
    iterate<First>(points, points_second, moves_x);
    if constexpr (First) return (int) points_second.size();
    std::set<day13::point, day13::comp> points_res;
    iterate<First>(points_second, points_res, moves_y);
    return (int) points_res.size();
}

day13::output_t day13::first_part(const day13::input_t &input) {
    return solve<true>(input.first, input.second.first, input.second.second);
}

day13::output_t day13::second_part(const day13::input_t &input) {
    return solve<false>(input.first, input.second.first, input.second.second);
}

day13::output_t day13::expected_p1() {
    return 790;
}

day13::output_t day13::expected_p2() {
    return 96;
}
