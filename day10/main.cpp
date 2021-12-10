#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#include "input.h"
#include "../common.h"

static const std::unordered_set<char> opening = {'(', '[', '{', '<'};

static std::unordered_map<char, char> m = {{')', '('},
                                           {']', '['},
                                           {'}', '{'},
                                           {'>', '<'},
                                           {'(', ')'},
                                           {'[', ']'},
                                           {'{', '}'},
                                           {'<', '>'}};

auto solve(auto &&line, auto &&stack, auto &&score) {
    for (auto &&s: line) {
        if (opening.contains(s)) stack.push_back(s);
        else if (stack.back() == m[s]) stack.pop_back();
        else return score[s];
    }
    return 0uLL;
}

auto first_part() {
    std::unordered_map<char, uint64_t> score = {{')', 3uLL},
                                                {']', 57uLL},
                                                {'}', 1197uLL},
                                                {'>', 25137uLL}};
    auto res = 0uLL;
    for (auto &&line: split(input, "\n")) {
        std::vector<char> stack;
        res += solve(line, stack, score);
    }
    return res;
}

auto second_part() {
    std::unordered_map<char, uint64_t> score = {{')', 1uLL},
                                                {']', 2uLL},
                                                {'}', 3uLL},
                                                {'>', 4uLL}};
    std::vector<uint64_t> scores;
    for (auto &&line: split(input, "\n")) {
        std::vector<char> stack;
        if (solve(line, stack, score) == 0uLL && !stack.empty()) {
            auto sc = 0uLL;
            for (auto i = (int32_t) stack.size() - 1; i >= 0; i--)
                sc = 5uLL * sc + score[m[stack[i]]];
            scores.push_back(sc);
        }
    }
    std::ranges::sort(scores);
    return scores[scores.size() / 2uLL];
}

int main() {
    std::cout << "First part: " << first_part() << std::endl;
    std::cout << "Second part: " << second_part() << std::endl;
    std::cout << sizeof(long);
    return 0;
}
