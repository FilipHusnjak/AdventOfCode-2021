#ifndef ADVENTOFCODE_2021_DAY04_H
#define ADVENTOFCODE_2021_DAY04_H

#include <unordered_map>

#include "../benchmark.h"

namespace day04 {
    struct board {
        board() {
            std::memset(rows, 5, sizeof(rows));
            std::memset(columns, 5, sizeof(columns));
        }

        int score = 0;
        std::unordered_map<int, std::pair<char, char>> m{};
        char rows[5]{};
        char columns[5]{};
    };

    using input_t = std::pair<std::vector<int>, std::list<board>>;
    using output_t = int;

    input_t parse(const parse_t &input);

    output_t first_part(const input_t &input);

    output_t second_part(const input_t &input);

    output_t expected_p1();

    output_t expected_p2();
}

#endif //ADVENTOFCODE_2021_DAY04_H
