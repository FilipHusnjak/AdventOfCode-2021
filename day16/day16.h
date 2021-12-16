#ifndef ADVENTOFCODE_2021_DAY16_H
#define ADVENTOFCODE_2021_DAY16_H

#include "../benchmark.h"

namespace day16 {
    using input_t = std::string;
    using output_t = long long;

    input_t parse(const parse_t &input);

    output_t first_part(const input_t &input);

    output_t second_part(const input_t &input);

    output_t expected_p1();

    output_t expected_p2();
}

#endif //ADVENTOFCODE_2021_DAY16_H
