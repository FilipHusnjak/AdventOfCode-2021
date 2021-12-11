#include <iostream>

#include "input.h"

#define NUM_ITER 100

constexpr int32_t dir_row[] = {0, 0, 1, -1, 1, 1, -1, -1};
constexpr int32_t dir_col[] = {1, -1, 0, 0, 1, -1, 1, -1};

consteval auto solve(auto second_p) {
    constexpr auto row_n = 10u, col_n = 10u;
    uint32_t m[row_n][col_n];
    for (auto row = 0u; row < row_n; row++)
        for (auto col = 0u; col < col_n; col++)
            m[row][col] = input[row * 11u + col] - '0';
    auto res = 0u;
    for (auto i = 0u; second_p || i < NUM_ITER; i++) {
        int32_t cnt = -1;
        std::pair<uint32_t, uint32_t> stack[row_n * col_n] = {};
        auto res_before = res;
        for (auto row = 0u; row < row_n; row++) {
            for (auto col = 0u; col < col_n; col++) {
                if (++m[row][col] == 10u) {
                    m[row][col] = 0u;
                    stack[++cnt] = {row, col};
                    res++;
                }
            }
        }
        while (cnt >= 0) {
            auto[row_idx, col_idx] = stack[cnt--];
            for (auto dir_idx = 0u; dir_idx < 8u; dir_idx++) {
                auto new_row_idx = row_idx + dir_row[dir_idx];
                auto new_col_idx = col_idx + dir_col[dir_idx];
                if (new_row_idx < 0 || new_col_idx < 0 || new_row_idx >= row_n || new_col_idx >= col_n ||
                    !m[new_row_idx][new_col_idx])
                    continue;
                if (++m[new_row_idx][new_col_idx] == 10u) {
                    m[new_row_idx][new_col_idx] = 0u;
                    stack[++cnt] = {new_row_idx, new_col_idx};
                    res++;
                }
            }
        }
        if (second_p && res - res_before == row_n * col_n) return i + 1u;
    }

    return res;
}

int main() {
    static_assert(solve(false) == 1691u);
    static_assert(solve(true) == 216u);
    return 0;
}
