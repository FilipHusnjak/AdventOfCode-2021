#include <array>
#include <algorithm>

#include "input.h"

consteval auto first_task() {
    auto cache = input;
    std::sort(cache.begin(), cache.end());
    auto amount = cache[cache.size() / 2];
    auto res = 0;
    for (auto &&c: cache)
        res += c - amount > 0 ? c - amount : amount - c;
    return res;
}

consteval auto count(auto f) {
    auto res = 0;
    for (auto &&i: input) {
        auto num = i - f > 0 ? i - f : f - i;
        res += num * (num + 1) / 2;
    }
    return res;
}

consteval auto second_task() {
    auto low = 0;
    for (auto &&i: input)
        low += i;
    low = low / (int32_t)input.size();
    return std::min(count(low), count(low + 1));
}

int main() {
    static_assert(first_task() == 342641);
    static_assert(second_task() == 93006301);
    return 0;
}
