#ifndef ADVENTOFCODE_2021_DAY10_H
#define ADVENTOFCODE_2021_DAY10_H

#include "../benchmark.h"

namespace day10 {
    using input_t = parse_t;
    using output_t = long long;

    input_t parse(const parse_t &input);

    output_t first_part(const input_t &input);

    output_t second_part(const input_t &input);

    output_t expected_p1();

    output_t expected_p2();
}

#endif //ADVENTOFCODE_2021_DAY10_H
