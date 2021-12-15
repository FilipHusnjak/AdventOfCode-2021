#ifndef ADVENTOFCODE_2021_DAY05_H
#define ADVENTOFCODE_2021_DAY05_H

#include <vector>

#include "../benchmark.h"

namespace day05 {
    using point = std::pair<int, int>;

    struct segment {
        point p_start;
        point p_end;
    };

    using input_t = std::vector<segment>;
    using output_t = int;

    input_t parse(const parse_t &input);

    output_t first_part(const input_t &input);

    output_t second_part(const input_t &input);

    output_t expected_p1();

    output_t expected_p2();
}

#endif //ADVENTOFCODE_2021_DAY05_H
