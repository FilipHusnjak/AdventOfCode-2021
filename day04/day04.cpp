#include "day04.h"

#include "../common.h"

day04::input_t day04::parse(const parse_t &input) {
    auto nums = split_int(input[0], ",");
    std::list<board> boards;
    for (int i = 2; i < input.size(); i += 6) {
        boards.emplace_back();
        for (char j = 0; j < 5; j++) {
            auto &&line = split_int(input[i + j]);
            for (char k = 0; k < 5; k++) {
                boards.rbegin()->m[line[k]] = {k, j};
                boards.rbegin()->score += line[k];
            }
        }
    }
    return {nums, boards};
}

template<auto Min>
int solve(const std::vector<int32_t> &nums, std::list<day04::board> boards) {
    if (boards.empty()) return 0;
    int32_t max_place = -1;
    auto max_b = *boards.begin();
    for (int32_t i = 0; i < nums.size(); i++) {
        if (boards.empty()) break;
        for (auto it = boards.begin(); it != boards.end();) {
            if (!it->m.contains(nums[i])) {
                it++;
                continue;
            }
            it->score -= nums[i];
            auto &&[row, col] = it->m.at(nums[i]);
            if (!--it->rows[row] || !--it->columns[col]) {
                if constexpr (Min) return it->score * nums[i];
                max_b = boards.size() == 1 ? *it : max_b;
                max_place = std::max(max_place, i);
                it = boards.erase(it);
            } else {
                it++;
            }
        }
    }
    return max_b.score * nums[max_place];
}

day04::output_t day04::first_part(const day04::input_t &input) {
    return solve<true>(input.first, input.second);
}

day04::output_t day04::second_part(const day04::input_t &input) {
    return solve<false>(input.first, input.second);
}

day04::output_t day04::expected_p1() {
    return 14093;
}

day04::output_t day04::expected_p2() {
    return 17388;
}
