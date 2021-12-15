#ifndef ADVENTOFCODE_2021_DAY12_H
#define ADVENTOFCODE_2021_DAY12_H

#include <unordered_map>

#include "../benchmark.h"

namespace day12 {
    using input_t = std::unordered_map<std::string_view, std::vector<std::string_view>>;
    using output_t = int;

    input_t parse(const parse_t &input);

    output_t first_part(const input_t &input);

    output_t second_part(const input_t &input);

    output_t expected_p1();

    output_t expected_p2();
}

#endif //ADVENTOFCODE_2021_DAY12_H
