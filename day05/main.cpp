#include <iostream>
#include <set>
#include <unordered_set>

#include "../common.h"

using point = std::pair<int64_t, int64_t>;

point &operator+=(point &l, const point &r) {
    l.first += r.first;
    l.second += r.second;
    return l;
}

point operator/(const point &p, int64_t d) {
    return {p.first / d, p.second / d};
}

point operator*(int64_t f, const point &p) {
    return {f * p.first, f * p.second};
}

point operator+(const point &l, const point &r) {
    return {l.first + r.first, l.second + r.second};
}

point operator-(const point &l, const point &r) {
    return {l.first - r.first, l.second - r.second};
}

int64_t operator^(const point &l, const point &r) {
    return l.first * r.second - l.second * r.first;
}

namespace std {
    template<>
    struct [[maybe_unused]] hash<point> {
        size_t operator()(const point &p) const {
            return (int64_t(p.first) << 32) + int64_t(p.second);
        }
    };
}

struct segment {
    point p_start;
    point p_end;
};

void intersect(const segment &s1, const segment &s2, std::unordered_set<point> &cache, uint32_t &count) {
    auto r = s1.p_end - s1.p_start;
    auto s = s2.p_end - s2.p_start;
    auto cross = r ^ s;
    auto cross2 = (s2.p_start - s1.p_start) ^ r;
    if (cross != 0) {
        auto cross3 = (s2.p_start - s1.p_start) ^ s;
        auto t = (double) cross3 / (double) cross;
        auto u = (double) cross2 / (double) cross;
        if (t < 0.0 || t > 1.0 || u < 0.0 || u > 1.0) return;
        auto d = (cross3 * r);
        if (d.first % cross != 0 || d.second % cross != 0) return;
        auto inter = s1.p_start + d / cross;
        count += cache.insert(inter).second;
    } else {
        if (cross2 != 0) return;
        auto p1 = std::max(s1.p_start, s2.p_start);
        auto p2 = std::min(s1.p_end, s2.p_end);
        if (p1 > p2) return;
        auto dir = p2 - p1;
        dir = {(dir.first != 0) * (dir.first > 0 ? 1 : -1),
               (dir.second != 0) * (dir.second > 0 ? 1 : -1)};
        for (auto p = p1;; p += dir) {
            count += cache.insert(p).second;
            if (p == p2) break;
        }
    }
}

auto count_intersections(const std::vector<segment> &segments) {
    uint32_t count = 0;
    std::unordered_set<point> cache;
    for (uint32_t i = 0; i < segments.size(); i++)
        for (uint32_t j = 0; j < i; j++)
            intersect(segments[i], segments[j], cache, count);
    return count;
}

int main() {
    std::vector<segment> f_segments;
    std::vector<segment> s_segments;
    for (std::string p1, p2, arr; std::cin >> p1 >> arr >> p2;) {
        auto &&pos1 = vector_to_pair(split<int64_t>(p1, ","));
        auto &&pos2 = vector_to_pair(split<int64_t>(p2, ","));
        auto p_start = std::min(pos1, pos2);
        auto p_end = std::max(pos1, pos2);
        if (pos1.first == pos2.first || pos1.second == pos2.second) f_segments.emplace_back(p_start, p_end);
        s_segments.emplace_back(p_start, p_end);
    }

    std::cout << "First part = " << count_intersections(f_segments) << std::endl;
    std::cout << "Second part = " << count_intersections(s_segments) << std::endl;

    return 0;
}
