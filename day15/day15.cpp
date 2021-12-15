#include "day15.h"

#include <queue>

day15::input_t day15::parse(const parse_t &input) {
    input_t res(input.size(), std::vector<int>(input[0].size()));
    for (int i = 0; auto &&line: input) {
        for (int j = 0; auto &&c: line)
            res[i][j++] = c - '0';
        i++;
    }
    return res;
}

template<typename F, typename S>
struct my_pair {
    F first;
    S second;
};

template<typename F, typename S>
bool operator>(const my_pair<F, S> &l, const my_pair<F, S> &r) {
    return l.first > r.first;
}

constexpr int dir_row[] = {0, 0, 1, -1};
constexpr int dir_col[] = {1, -1, 0, 0};

template<auto N>
day15::output_t solve(const day15::input_t &input) {
    std::vector<std::vector<int>> m(input.size() * N,
                                    std::vector<int>(input[0].size() * N, std::numeric_limits<int>::max()));
    std::vector<std::vector<char>> visited(input.size() * N, std::vector<char>(input[0].size() * N, false));
    int s_s1 = (int) input.size(), s_s2 = (int) input[0].size();
    int s_l1 = N * s_s1, s_l2 = N * s_s2;
    std::priority_queue<my_pair<int, my_pair<int, int>>, std::vector<my_pair<int, my_pair<int, int>>>, std::greater<>> q;
    q.push({0, {0, 0}});
    m[0][0] = 0;
    while (!q.empty()) {
        auto curr = q.top();
        q.pop();
        visited[curr.second.first][curr.second.second] = true;
        if (curr.second.first == s_l1 - 1 && curr.second.second == s_l2 - 1) return curr.first;
        auto &&[row, col] = curr.second;
        for (int i = 0; i < 4; i++) {
            int new_row = row + dir_row[i];
            int new_col = col + dir_col[i];
            if (new_row < 0 || new_col < 0 || new_row >= s_l1 || new_col >= s_l2 || visited[new_row][new_col]) continue;
            int wrapped = input[new_row % s_s1][new_col % s_s2] + new_row / s_s1 + new_col / s_s2;
            int new_v = m[row][col] + (wrapped > 9 ? wrapped - 9 : wrapped);
            if (new_v >= m[new_row][new_col]) continue;
            m[new_row][new_col] = new_v;
            q.push({new_v, {new_row, new_col}});
        }
    }
    return 0;
}

day15::output_t day15::first_part(const day15::input_t &input) {
    return solve<1>(input);
}

day15::output_t day15::second_part(const day15::input_t &input) {
    return solve<5>(input);
}

day15::output_t day15::expected_p1() {
    return 755;
}

day15::output_t day15::expected_p2() {
    return 3016;
}
