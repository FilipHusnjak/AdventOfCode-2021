#ifndef ADVENTOFCODE_2021_DAY06_H
#define ADVENTOFCODE_2021_DAY06_H

#include <array>

#include "../benchmark.h"

namespace day06 {
    using input_t = std::array<long long, 9>;
    using output_t = long long;

    input_t parse(const parse_t &input);

    output_t first_part(const input_t &input);

    output_t second_part(const input_t &input);

    output_t expected_p1();

    output_t expected_p2();
}

#endif //ADVENTOFCODE_2021_DAY06_H
