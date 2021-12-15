#ifndef ADVENTOFCODE_2021_DAY08_H
#define ADVENTOFCODE_2021_DAY08_H

#include <unordered_set>

#include "../benchmark.h"

namespace day08 {
    using input_t = std::vector<std::pair<std::vector<std::unordered_set<char>>, std::vector<std::string>>>;
    using output_t = int;

    input_t parse(const parse_t &input);

    output_t first_part(const input_t &input);

    output_t second_part(const input_t &input);

    output_t expected_p1();

    output_t expected_p2();
}

#endif //ADVENTOFCODE_2021_DAY08_H
