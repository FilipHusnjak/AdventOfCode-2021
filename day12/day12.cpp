#include "day12.h"

#include "../common.h"

day12::input_t day12::parse(const parse_t &input) {
    input_t res;
    for (auto &&line: input) {
        auto &&[l, r] = vector_to_pair(split_str(line, "-"));
        res[l].push_back(r);
        res[r].push_back(l);
    }
    return res;
}

int solve(day12::input_t &m, auto &&visited, const std::string_view &curr, char twice) {
    visited[curr]++;
    auto res = 0;
    for (auto &&next: m[curr]) {
        if (next == "end") res++;
        else if (!islower(next[0]) || !visited[next]) res += solve(m, visited, next, twice);
        else if (next != "start" && !twice) res += solve(m, visited, next, true);
    }
    visited[curr]--;
    return res;
}

day12::output_t day12::first_part(const day12::input_t &input) {
    std::unordered_map<std::string_view, uint8_t> visited;
    std::string start = "start";
    visited[start] = 1;
    auto m = input;
    return solve(m, visited, start, true);
}

day12::output_t day12::second_part(const day12::input_t &input) {
    std::unordered_map<std::string_view, uint8_t> visited;
    std::string start = "start";
    visited[start] = 1;
    auto m = input;
    return solve(m, visited, start, false);
}

day12::output_t day12::expected_p1() {
    return 3463;
}

day12::output_t day12::expected_p2() {
    return 91533;
}
