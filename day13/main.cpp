#include <iostream>
#include <string>
#include <set>
#include <algorithm>

#include "../common.h"
#include "input.h"

using point = std::pair<int32_t, int32_t>;

struct comp {
    bool operator()(const point &l, const point &r) const {
        if (l.first == r.first) return l.second > r.second;
        return l.first > r.first;
    }
};

auto iterate(auto &&points, auto &&points_out, auto &&moves) {
    std::vector<int32_t> accumulated;
    auto it = points.begin();
    for (int32_t i = (int32_t) moves.size() - 1; i >= 0; i--) {
        while (it != points.end() && it->first > moves[i]) {
            points.emplace(2 * moves[i] - it->first, it->second);
            it = points.erase(it);
        }
    }
    for (auto &&p: points)
        points_out.emplace(p.second, p.first);
}

auto solve(auto &&points, auto &&moves_x, auto &&moves_y, auto max_x, auto max_y) {
    std::set<point, comp> points_second;
    iterate(points, points_second, moves_x);
    std::set<point, comp> points_res;
    iterate(points_second, points_res, moves_y);
    for (int i = 0; i <= max_y; i++) {
        for (int j = 0; j <= max_x; j++)
            std::cout << (points_res.contains({j, i}) ? "#" : ".");
        std::cout << std::endl;
    }
    return points_res.size();
}

int main() {
    std::set<point, comp> points;
    int32_t max_x = -1, max_y = -1;
    for (auto &&line: split(input, "\n")) {
        auto &&[x, y] = vector_to_pair(split_num<int32_t>(line, ","));
        max_x = std::max(max_x, x);
        max_y = std::max(max_y, y);
        points.emplace(x, y);
    }
    std::vector<int32_t> moves_x;
    std::vector<int32_t> moves_y;
    for (auto &&line: split(m, "\n")) {
        auto &&v = split(split(line, " ")[2], "=");
        auto num = std::strtol(&*v[1].begin(), nullptr, 10);
        if (v[0] == "x") {
            moves_x.push_back(num);
            max_x -= (max_x - num + 1);
        } else {
            moves_y.push_back(num);
            max_y -= (max_y - num + 1);
        }
    }
    std::sort(moves_x.begin(), moves_x.end());
    std::sort(moves_y.begin(), moves_y.end());
    std::cout << solve(points, moves_x, moves_y, max_x, max_y) << std::endl;
    return 0;
}
