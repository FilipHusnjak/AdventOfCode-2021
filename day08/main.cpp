#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <array>

#include "input.h"
#include "../common.h"

template<auto... Nums>
auto contains(auto n) {
    return ((n == Nums) || ...);
}

auto first_part() {
    auto count = 0;
    for (auto &&view: split(input, "\n"))
        for (auto &&v: split(*split(view, " | ").rbegin(), " "))
            count += contains<2, 3, 4, 7>(v.size());
    return count;
}

namespace std {
    template<>
    struct [[maybe_unused]] hash<std::unordered_set<int8_t>> {
        auto operator()(auto &&s) const {
            auto h = 0;
            for (auto si: s)
                h += std::hash<decltype(si)>()(si);
            return h;
        }
    };
}

template<typename... Args>
auto assign(auto &&nums, auto &&sorted, Args &&... args) {
    ((nums[{sorted[args.first].begin(), sorted[args.first].end()}] = args.second), ...);
}

template<auto L, auto H, auto C, typename... Ignore>
auto find_num(auto &&nums, auto &&part, Ignore &&... ignore) {
    for (auto i = L; i < H; i++) {
        if constexpr(C) {
            if (((i != ignore) && ...) && std::ranges::all_of(part, [&](auto &&el) { return nums[i].contains(el); }))
                return i;
        } else {
            if (((i != ignore) && ...) &&
                std::ranges::all_of(nums[i], [&](auto &&el) { return part.contains(el); }))
                return i;
        }
    }
    return L;
}

auto second_part() {
    auto res = 0;
    for (auto &&line: split(input, "\n")) {
        std::unordered_map<std::unordered_set<int8_t>, int32_t> nums;
        auto &&parts = split(line, " | ");
        auto &&first = split<std::unordered_set<int8_t>>(*parts.begin(), " ");
        std::sort(first.begin(), first.end(),
                  [](auto &&str1, auto &&str2) { return str1.size() < str2.size(); });
        const auto one = 0;
        const auto seven = 1;
        const auto four = 2;
        const auto eight = 9;
        const auto three = find_num<3, 6, true>(first, first[one]);
        const auto nine = find_num<6, 9, true>(first, first[four]);
        const auto zero = find_num<6, 9, true>(first, first[one], nine);
        const auto five = find_num<3, 6, false>(first, first[nine], three);
        const auto two = 12 - three - five;
        const auto six = 21 - zero - nine;

        assign(nums, first, std::make_pair(zero, 0), std::make_pair(one, 1), std::make_pair(two, 2),
               std::make_pair(three, 3), std::make_pair(four, 4), std::make_pair(five, 5), std::make_pair(six, 6),
               std::make_pair(seven, 7), std::make_pair(eight, 8), std::make_pair(nine, 9));

        auto &&second = split(*parts.rbegin(), " ");
        auto num = 0;
        for (auto &&s: second)
            num = num * 10 + nums[{s.begin(), s.end()}];
        res += num;
    }
    return res;
}

int main() {
    std::cout << first_part() << std::endl;
    std::cout << second_part() << std::endl;
    return 0;
}
