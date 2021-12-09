#include <iostream>
#include <queue>
#include <set>

#include "input.h"
#include "../common.h"

int32_t dir_y[] = {0, 0, 1, -1};
int32_t dir_x[] = {1, -1, 0, 0};

auto is_low(auto &&m, auto start_y, auto start_x) {
    for (auto i = 0; i < 4; i++) {
        auto y = start_y + dir_y[i];
        auto x = start_x + dir_x[i];
        if (y >= 0 && x >= 0 && y < m.size() && x < m[y].size() && m[y][x] <= m[start_y][start_x]) return false;
    }
    return true;
}

auto get_lows(auto &&m) {
    std::vector<std::pair<int32_t, int32_t>> lows;
    for (auto y = 0; y < m.size(); y++)
        for (auto x = 0; x < m[y].size(); x++)
            if (is_low(m, y, x)) lows.emplace_back(y, x);
    return lows;
}

auto first_part(auto &&m, auto lows) {
    auto res = 0;
    for (auto[y, x]: lows)
        res += m[y][x] + 1;
    return res;
}

auto dfs(auto &&m, auto &&visited, auto low_y, auto low_x, auto high) {
    std::vector stack = {std::make_pair(low_y, low_x)};
    visited[low_y][low_x] = true;
    auto count = 0;
    while (!stack.empty()) {
        auto[start_y, start_x] = stack.back();
        stack.pop_back();
        count++;
        for (auto i = 0; i < 4; i++) {
            auto y = start_y + dir_y[i];
            auto x = start_x + dir_x[i];
            if (y >= 0 && x >= 0 && y < m.size() && x < m[y].size() && !visited[y][x] && m[y][x] < high) {
                stack.emplace_back(y, x);
                visited[y][x] = true;
            }
        }
    }
    return count;
}

auto second_part(auto &&m, auto lows, auto high) {
    std::multiset<int32_t> best;
    std::vector visited(m.size(), std::vector<int8_t>(m[0].size(), 0));
    for (auto[y, x]: lows) {
        auto cnt = dfs(m, visited, y, x, high);
        if (best.size() < 3) {
            best.insert(cnt);
        } else if (*best.begin() < cnt) {
            best.erase(best.begin());
            best.insert(cnt);
        }
    }
    auto res = 1;
    for (auto b: best)
        res *= b;
    return res;
}

int main() {
    auto &&lines = split(input, "\n");
    if (lines.empty()) return 0;
    std::vector m(lines.size(), std::vector<int32_t>(lines[0].size()));
    auto high = -1;
    for (auto y = 0; auto &&line: lines) {
        for (auto x = 0; auto &&s: line)
            high = std::max(high, m[y][x++] = s - '0');
        y++;
    }

    auto lows = get_lows(m);

    std::cout << "First part = " << first_part(m, lows) << std::endl;
    std::cout << "Second part = " << second_part(m, lows, high) << std::endl;

    return 0;
}
