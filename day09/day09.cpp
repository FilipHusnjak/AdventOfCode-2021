#include "day09.h"

#include <set>

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

day09::input_t day09::parse(const parse_t &input) {
    input_t res(std::vector<std::vector<int>>(input.size(), std::vector<int>(input[0].size())), {});
    for (auto y = 0; auto &&line: input) {
        for (auto x = 0; auto &&s: line)
            res.first[y][x++] = s - '0';
        y++;
    }
    for (auto y = 0; y < res.first.size(); y++)
        for (auto x = 0; x < res.first[y].size(); x++)
            if (is_low(res.first, y, x)) res.second.emplace_back(y, x);
    return res;
}

day09::output_t day09::first_part(const day09::input_t &input) {
    auto res = 0;
    for (auto[y, x]: input.second)
        res += input.first[y][x] + 1;
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

day09::output_t day09::second_part(const day09::input_t &input) {
    int high = -1;
    for (const auto &y: input.first)
        for (int x: y)
            high = std::max(high, x);
    std::multiset<int> best;
    std::vector visited(input.first.size(), std::vector<int8_t>(input.first[0].size(), 0));
    for (auto[y, x]: input.second) {
        auto cnt = dfs(input.first, visited, y, x, high);
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

day09::output_t day09::expected_p1() {
    return 530;
}

day09::output_t day09::expected_p2() {
    return 1019494;
}
