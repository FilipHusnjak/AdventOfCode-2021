#ifndef ADVENTOFCODE_2021_DAY14_H
#define ADVENTOFCODE_2021_DAY14_H

#include <list>
#include <unordered_map>

#include "../benchmark.h"

namespace day14 {
    using input_t = std::pair<std::pair<std::unordered_map<std::pair<char, char>, std::pair<long long, long long>>, std::unordered_map<char, long long>>, std::unordered_map<std::pair<char, char>, char>>;
    using output_t = long long;

    input_t parse(const parse_t &input);

    output_t first_part(const input_t &input);

    output_t second_part(const input_t &input);

    output_t expected_p1();

    output_t expected_p2();
}

#endif //ADVENTOFCODE_2021_DAY14_H
