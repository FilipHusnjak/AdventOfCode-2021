#ifndef ADVENTOFCODE_2021_DAY02_H
#define ADVENTOFCODE_2021_DAY02_H

#include <vector>

#include "../benchmark.h"

namespace day02 {
    using input_t = std::vector<std::pair<int, int>>;
    using output_t = int;

    input_t parse(const parse_t &input);

    output_t first_part(const input_t &input);

    output_t second_part(const input_t &input);

    output_t expected_p1();

    output_t expected_p2();
}

#endif //ADVENTOFCODE_2021_DAY02_H
