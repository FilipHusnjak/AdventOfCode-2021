#include <array>

#include "input.h"

consteval auto get_states() {
    std::array<int64_t, 9> states{};
    for (auto &&i: input)
        states[i]++;
    return states;
}

template<size_t N>
consteval auto solve() {
    auto states = get_states();
    for (int32_t i = 0; i < N; i++) {
        auto next = states[0];
        for (int32_t j = 0; j < 8; j++)
            states[j] = states[j + 1];
        states[6] += next;
        states[8] = next;
    }
    int64_t res = 0;
    for (auto &&s: states)
        res += s;
    return res;
}

int main() {
    static_assert(solve<80>() == 379414);
    static_assert(solve<256>() == 1705008653296);
    return 0;
}
