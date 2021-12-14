#include <iostream>
#include <vector>
#include <unordered_map>
#include <ranges>
#include <algorithm>

#include "../common.h"

struct board {
    board() {
        std::memset(rows, 5, sizeof(rows));
        std::memset(columns, 5, sizeof(columns));
    }

    uint32_t score = 0;
    std::unordered_map<int32_t, std::pair<uint8_t, uint8_t>> m{};
    uint8_t rows[5]{};
    uint8_t columns[5]{};
};

auto calculate_min_max(const std::vector<int32_t> &nums, std::list<board> &boards) {
    if (boards.empty()) return std::make_pair(0u, 0u);
    int32_t init_size = (int32_t) boards.size(), min_place = (int32_t) nums.size(), max_place = -1;
    auto min_b = *boards.begin(), max_b = *boards.begin();
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
                min_b = boards.size() == init_size ? *it : min_b;
                max_b = boards.size() == 1 ? *it : max_b;
                min_place = std::min(min_place, i);
                max_place = std::max(max_place, i);
                it = boards.erase(it);
            } else {
                it++;
            }
        }
    }
    return std::make_pair(min_b.score * nums[min_place], max_b.score * nums[max_place]);
}

auto parse_boards() {
    std::list<board> boards;
    while (true) {
        boards.emplace_back();
        for (uint8_t col = 0; col < 5; ++col) {
            for (uint8_t row = 0; row < 5; ++row) {
                int32_t num;
                if (!(std::cin >> num)) return std::list<board>(boards.begin(), --boards.end());
                boards.rbegin()->m[num] = {row, col};
                boards.rbegin()->score += num;
            }
        }
    }
}

int main() {
    std::string line;
    std::cin >> line;
    auto nums = split_num<int32_t>(line, ",");
    auto boards = parse_boards();

    const auto &&[f, s] = calculate_min_max(nums, boards);

    std::cout << "First part = " << f << std::endl;
    std::cout << "Second part = " << s << std::endl;

    return 0;
}
