#include <iostream>
#include <unordered_map>

#include "../common.h"
#include "input.h"

size_t solve(auto &&m, auto &&visited, auto &&curr, auto twice) {
    visited[curr]++;
    auto res = 0u;
    for (auto &&next: m[curr]) {
        if (next == "end") res++;
        else if (!islower(next[0]) || !visited[next]) res += solve(m, visited, next, twice);
        else if (next != "start" && !twice) res += solve(m, visited, next, true);
    }
    visited[curr]--;
    return res;
}

int main() {
    std::unordered_map<std::string_view, std::vector<std::string_view>> m;
    std::unordered_map<std::string_view, uint8_t> visited;
    for (auto &&line: split(input, "\n")) {
        auto &&[l, r] = vector_to_pair(split(line, "-"));
        m[l].push_back(r);
        m[r].push_back(l);
    }
    std::string start = "start";
    visited[start] = 1;
    std::cout << "First part = " << solve(m, visited, start, true) << std::endl;
    std::cout << "Second part = " << solve(m, visited, start, false) << std::endl;
    return 0;
}
