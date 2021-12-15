#include "day10.h"

#include <unordered_map>
#include <unordered_set>
#include <ranges>
#include <algorithm>

static const std::unordered_set<char> opening = {'(', '[', '{', '<'};

static std::unordered_map<char, char> m = {{')', '('},
                                           {']', '['},
                                           {'}', '{'},
                                           {'>', '<'},
                                           {'(', ')'},
                                           {'[', ']'},
                                           {'{', '}'},
                                           {'<', '>'}};

day10::input_t day10::parse(const parse_t &input) {
    return input;
}

long long solve(const std::string &line, std::vector<char> &stack, std::unordered_map<char, long long> &score) {
    for (auto &&s: line) {
        if (opening.contains(s)) stack.push_back(s);
        else if (stack.back() == m[s]) stack.pop_back();
        else return score[s];
    }
    return 0LL;
}

day10::output_t day10::first_part(const input_t &input) {
    std::unordered_map<char, long long> score = {{')', 3uLL},
                                                 {']', 57uLL},
                                                 {'}', 1197uLL},
                                                 {'>', 25137uLL}};
    auto res = 0LL;
    for (auto &&line: input) {
        std::vector<char> stack;
        res += solve(line, stack, score);
    }
    return res;
}

day10::output_t day10::second_part(const input_t &input) {
    std::unordered_map<char, long long> score = {{')', 1LL},
                                                 {']', 2LL},
                                                 {'}', 3LL},
                                                 {'>', 4LL}};
    std::vector<long long> scores;
    for (auto &&line: input) {
        std::vector<char> stack;
        if (solve(line, stack, score) == 0LL && !stack.empty()) {
            auto sc = 0LL;
            for (auto i = (int) stack.size() - 1; i >= 0; i--)
                sc = 5LL * sc + score[m[stack[i]]];
            scores.push_back(sc);
        }
    }
    std::ranges::sort(scores);
    return (long long) scores[scores.size() / 2LL];
}

day10::output_t day10::expected_p1() {
    return 345441;
}

day10::output_t day10::expected_p2() {
    return 3235371166;
}
