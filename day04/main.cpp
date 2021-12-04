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

    bool operator<(const board &other) const {
        return place < other.place;
    }

    uint32_t place = 0;
    std::unordered_map<int32_t, std::pair<uint8_t, uint8_t>> m{};
    uint8_t rows[5]{};
    uint8_t columns[5]{};
};

auto get_score(int32_t last, const board &b) {
    int score = 0;
    for (auto &&[k, v]: b.m) {
        if (k == last) continue;
        score += (int32_t) k;
    }
    return score * last;
}

auto calculate_min_max(const std::vector<int32_t> &nums, std::vector<board> boards) {
    for (uint32_t i = 0; i < nums.size(); i++) {
        for (auto &&b: boards) {
            if (b.place > 0 || !b.m.contains(nums[i])) continue;
            if (!--b.rows[b.m.at(nums[i]).first] || !--b.columns[b.m.at(nums[i]).second]) b.place = i;
            b.m.erase(nums[i]);
        }
    }
    const auto &&[res1, res2] = std::minmax_element(boards.begin(), boards.end());
    return std::make_pair(get_score(nums[res1->place], *res1), get_score(nums[res2->place], *res2));
}

auto parse_boards() {
    std::vector<board> boards;
    while (true) {
        boards.emplace_back();
        for (uint8_t col = 0; col < 5; ++col) {
            for (uint8_t row = 0; row < 5; ++row) {
                int32_t num;
                if (!(std::cin >> num)) return std::vector<board>(boards.begin(), --boards.end());
                boards.rbegin()->m[num] = {row, col};
            }
        }
    }
}

int main() {
    std::string line;
    std::cin >> line;
    std::vector<int32_t> nums = split(line, ',');
    std::vector<board> boards = parse_boards();

    const auto &&[f, s] = calculate_min_max(nums, boards);

    std::cout << "First part = " << f << std::endl;
    std::cout << "Second part = " << s << std::endl;

    return 0;
}
