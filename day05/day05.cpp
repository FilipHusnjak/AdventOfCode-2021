#include "day05.h"

#include <unordered_set>

#include "../common.h"

day05::input_t day05::parse(const parse_t &input) {
    input_t res;
    for (auto &&line: input) {
        auto[p1, p2] = vector_to_pair(split_str(line, "->"));
        auto &&pos1 = vector_to_pair(split_int(p1, ","));
        auto &&pos2 = vector_to_pair(split_int(p2, ","));
        auto p_start = std::min(pos1, pos2);
        auto p_end = std::max(pos1, pos2);
        res.emplace_back(p_start, p_end);
    }
    return res;
}

day05::point &operator+=(day05::point &l, const day05::point &r) {
    l.first += r.first;
    l.second += r.second;
    return l;
}

day05::point operator/(const day05::point &p, int d) {
    return {p.first / d, p.second / d};
}

day05::point operator*(int f, const day05::point &p) {
    return {f * p.first, f * p.second};
}

day05::point operator+(const day05::point &l, const day05::point &r) {
    return {l.first + r.first, l.second + r.second};
}

day05::point operator-(const day05::point &l, const day05::point &r) {
    return {l.first - r.first, l.second - r.second};
}

int operator^(const day05::point &l, const day05::point &r) {
    return l.first * r.second - l.second * r.first;
}

namespace std {
    template<>
    struct [[maybe_unused]]  [[maybe_unused]] hash<day05::point> {
        size_t operator()(const day05::point &p) const {
            return (int64_t(p.first) << 32) + int64_t(p.second);
        }
    };
}

namespace day05 {
    void intersect(const segment &s1, const segment &s2, std::unordered_set<point> &cache, int &count) {
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
}

day05::output_t day05::first_part(const day05::input_t &input) {
    int count = 0;
    std::unordered_set<point> cache;
    for (int i = 0; i < input.size(); i++) {
        if (input[i].p_start.first != input[i].p_end.first && input[i].p_start.second != input[i].p_end.second)
            continue;
        for (int j = 0; j < i; j++) {
            if (input[j].p_start.first != input[j].p_end.first &&
                input[j].p_start.second != input[j].p_end.second)
                continue;
            intersect(input[i], input[j], cache, count);
        }
    }
    return count;
}

day05::output_t day05::second_part(const input_t &input) {
    int count = 0;
    std::unordered_set<point> cache;
    for (int i = 0; i < input.size(); i++)
        for (int j = 0; j < i; j++)
            intersect(input[i], input[j], cache, count);
    return count;
}

day05::output_t day05::expected_p1() {
    return 6397;
}

day05::output_t day05::expected_p2() {
    return 22335;
}
