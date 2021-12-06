#include <array>

constexpr std::array<int64_t, 300> input = {3, 4, 1, 1, 5, 1, 3, 1, 1, 3, 5, 1, 1, 5, 3, 2, 4, 2, 2, 2, 1, 1, 1, 1, 5,
                                            1, 1, 1, 1, 1, 3, 1, 1, 5, 4, 1, 1, 1, 4, 1, 1, 1, 1, 2, 3, 2, 5, 1, 5, 1,
                                            2, 1, 1, 1, 4, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 2, 3, 4, 2, 1, 3,
                                            1, 1, 2, 1, 1, 2, 1, 5, 2, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 5, 1, 4, 1, 1,
                                            1, 3, 3, 1, 3, 1, 3, 1, 4, 1, 1, 1, 1, 1, 4, 5, 1, 1, 3, 2, 2, 5, 5, 4, 3,
                                            1, 2, 1, 1, 1, 4, 1, 3, 4, 1, 1, 1, 1, 2, 1, 1, 3, 2, 1, 1, 1, 1, 1, 4, 1,
                                            1, 1, 4, 4, 5, 2, 1, 1, 1, 1, 1, 2, 4, 2, 1, 1, 1, 2, 1, 1, 2, 1, 5, 1, 5,
                                            2, 5, 5, 1, 1, 3, 1, 4, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 4, 1, 1, 1, 1, 1, 2,
                                            1, 2, 1, 1, 1, 5, 1, 1, 3, 5, 1, 1, 5, 5, 3, 5, 3, 4, 1, 1, 1, 3, 1, 1, 3,
                                            1, 1, 1, 1, 1, 1, 5, 1, 3, 1, 5, 1, 1, 4, 1, 3, 1, 1, 1, 2, 1, 1, 1, 2, 1,
                                            5, 1, 1, 1, 1, 4, 1, 3, 2, 3, 4, 1, 3, 5, 3, 4, 1, 4, 4, 4, 1, 3, 2, 4, 1,
                                            4, 1, 1, 2, 1, 3, 1, 5, 5, 1, 5, 1, 1, 1, 5, 2, 1, 2, 3, 1, 4, 3, 3, 4, 3};

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
