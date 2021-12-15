#include "day08.h"

#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#include "../common.h"

day08::input_t day08::parse(const parse_t &input) {
    input_t res;
    for (auto &&line: input) {
        auto[f, s] = vector_to_pair(split_str(line, " | "));
        res.emplace_back(split_str<std::unordered_set<char>>(f, " "), split_str<std::string>(s, " "));
    }
    return res;
}

template<auto... Nums>
auto contains(auto n) {
    return ((n == Nums) || ...);
}

day08::output_t day08::first_part(const day08::input_t &input) {
    auto count = 0;
    for (auto &&line: input)
        for (auto &&l: line.second)
            count += contains<2, 3, 4, 7>(l.size());
    return count;
}

namespace std {
    template<>
    struct [[maybe_unused]] hash<std::unordered_set<char>> {
        size_t operator()(auto &&s) const {
            size_t h = 0uLL;
            for (char si: s)
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

day08::output_t day08::second_part(const day08::input_t &input) {
    auto res = 0;
    for (auto line: input) {
        std::unordered_map<std::unordered_set<char>, int> nums;
        std::sort(line.first.begin(), line.first.end(),
                  [](auto &&l, auto &&r) { return l.size() < r.size(); });
        const auto one = 0;
        const auto seven = 1;
        const auto four = 2;
        const auto eight = 9;
        const auto three = find_num<3, 6, true>(line.first, line.first[one]);
        const auto nine = find_num<6, 9, true>(line.first, line.first[four]);
        const auto zero = find_num<6, 9, true>(line.first, line.first[one], nine);
        const auto five = find_num<3, 6, false>(line.first, line.first[nine], three);
        const auto two = 12 - three - five;
        const auto six = 21 - zero - nine;

        assign(nums, line.first, std::make_pair(zero, 0), std::make_pair(one, 1), std::make_pair(two, 2),
               std::make_pair(three, 3), std::make_pair(four, 4), std::make_pair(five, 5), std::make_pair(six, 6),
               std::make_pair(seven, 7), std::make_pair(eight, 8), std::make_pair(nine, 9));

        auto num = 0;
        for (auto &&s: line.second)
            num = num * 10 + nums[{s.begin(), s.end()}];
        res += num;
    }
    return res;
}

day08::output_t day08::expected_p1() {
    return 375;
}

day08::output_t day08::expected_p2() {
    return 1019355;
}
