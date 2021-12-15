#ifndef ADVENTOFCODE_2021_DAY13_H
#define ADVENTOFCODE_2021_DAY13_H

#include <set>

#include "../benchmark.h"

namespace day13 {
    using point = std::pair<int, int>;

    struct comp {
        bool operator()(const point &l, const point &r) const {
            if (l.first == r.first) return l.second > r.second;
            return l.first > r.first;
        }
    };

    using input_t = std::pair<std::set<point, comp>, std::pair<std::vector<int>, std::vector<int>>>;
    using output_t = int;

    input_t parse(const parse_t &input);

    output_t first_part(const input_t &input);

    output_t second_part(const input_t &input);

    output_t expected_p1();

    output_t expected_p2();
}

#endif //ADVENTOFCODE_2021_DAY13_H
