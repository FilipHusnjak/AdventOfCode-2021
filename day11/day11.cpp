#include "day11.h"

#define NUM_ITER 100

constexpr int dir_row[] = {0, 0, 1, -1, 1, 1, -1, -1};
constexpr int dir_col[] = {1, -1, 0, 0, 1, -1, 1, -1};

day11::input_t day11::parse(const parse_t &input) {
    input_t res{};
    for (int i = 0; i < input.size(); i++)
        for (int j = 0; auto &&s: input[i])
            res[i][j++] = s - '0';
    return res;
}

auto solve(auto &&input, auto second_p) {
    constexpr auto row_n = 10, col_n = 10;
    auto m = input;
    auto res = 0;
    for (auto i = 0; second_p || i < NUM_ITER; i++) {
        int cnt = -1;
        std::pair<int, int> stack[row_n * col_n] = {};
        auto res_before = res;
        for (auto row = 0; row < row_n; row++) {
            for (auto col = 0; col < col_n; col++) {
                if (++m[row][col] == 10) {
                    m[row][col] = 0;
                    stack[++cnt] = {row, col};
                    res++;
                }
            }
        }
        while (cnt >= 0) {
            auto[row_idx, col_idx] = stack[cnt--];
            for (auto dir_idx = 0; dir_idx < 8; dir_idx++) {
                auto new_row_idx = row_idx + dir_row[dir_idx];
                auto new_col_idx = col_idx + dir_col[dir_idx];
                if (new_row_idx < 0 || new_col_idx < 0 || new_row_idx >= row_n || new_col_idx >= col_n ||
                    !m[new_row_idx][new_col_idx])
                    continue;
                if (++m[new_row_idx][new_col_idx] == 10) {
                    m[new_row_idx][new_col_idx] = 0;
                    stack[++cnt] = {new_row_idx, new_col_idx};
                    res++;
                }
            }
        }
        if (second_p && res - res_before == row_n * col_n) return i + 1;
    }

    return res;
}

day11::output_t day11::first_part(const day11::input_t &input) {
    return solve(input, false);
}

day11::output_t day11::second_part(const day11::input_t &input) {
    return solve(input, true);
}

day11::output_t day11::expected_p1() {
    return 1691;
}

day11::output_t day11::expected_p2() {
    return 216;
}

