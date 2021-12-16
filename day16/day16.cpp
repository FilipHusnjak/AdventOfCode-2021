#include "day16.h"

#include <charconv>
#include <unordered_map>

std::unordered_map<char, std::string> m = {{'0', "0000"},
                                           {'1', "0001"},
                                           {'2', "0010"},
                                           {'3', "0011"},
                                           {'4', "0100"},
                                           {'5', "0101"},
                                           {'6', "0110"},
                                           {'7', "0111"},
                                           {'8', "1000"},
                                           {'9', "1001"},
                                           {'A', "1010"},
                                           {'B', "1011"},
                                           {'C', "1100"},
                                           {'D', "1101"},
                                           {'E', "1110"},
                                           {'F', "1111"}};

constexpr long long max(long long a, long long b) {
    return a > b ? a : b;
}

constexpr long long min(long long a, long long b) {
    return a < b ? a : b;
}

constexpr long long plus(long long a, long long b) {
    return a + b;
}

constexpr long long mult(long long a, long long b) {
    return a * b;
}

constexpr bool less(long long a, long long b) {
    return a < b;
}

constexpr bool greater(long long a, long long b) {
    return a > b;
}

constexpr bool equal(long long a, long long b) {
    return a == b;
}

day16::input_t day16::parse(const parse_t &input) {
    std::string res;
    for (auto c: input[0])
        res += m[c];
    return res;
}

inline auto to_int(auto &&begin, auto &&end) {
    int res;
    std::from_chars(begin, end, res, 2);
    return res;
}

auto solve(auto it, const auto end, long long &version_sum, long long &value) -> decltype(it) {
    if (it == end || end - it < 6) return end;
    long long version = to_int(&it[0], &it[3]);
    version_sum += version;
    int type = to_int(&it[3], &it[6]);
    if (type == 4) {
        value = 0;
        for (it += 7; it != end; it++) {
            for (int i = 0; i < 4; i++, it++)
                value = value * 2 + (*it == '1');
            if (*(it - 5) == '0') return it;
        }
        return it; // Should never happen
    } else {
        std::vector<long long> values;
        if (it[6] == '0') {
            int num_bits = to_int(&it[7], &it[22]);
            auto new_end = (it += 22) + num_bits;
            while (it != new_end) {
                long long new_v;
                it = solve(it, end, version_sum, new_v);
                values.push_back(new_v);
            }
        } else {
            int num_packets = to_int(&it[7], &it[18]);
            it += 18;
            for (int i = 0; i < num_packets; i++) {
                long long new_v;
                it = solve(it, end, version_sum, new_v);
                values.push_back(new_v);
            }
        }
        if (type < 4) {
            if (values.empty()) return it;
            auto f = type == 0 ? plus : (type == 1 ? mult : (type == 2 ? min : max));
            value = values[0];
            for (int i = 1; i < values.size(); i++) value = f(value, values[i]);
        } else {
            if (values.size() < 2) return it;
            auto f = type == 5 ? greater : (type == 6 ? less : equal);
            value = f(values[0], values[1]);
        }
        return it;
    }
}

day16::output_t day16::first_part(const day16::input_t &input) {
    long long version_sum = 0LL, value;
    solve(input.begin(), input.end(), version_sum, value);
    return version_sum;
}

day16::output_t day16::second_part(const day16::input_t &input) {
    long long version_sum = 0, value;
    solve(input.begin(), input.end(), version_sum, value);
    return value;
}

day16::output_t day16::expected_p1() {
    return 940LL;
}

day16::output_t day16::expected_p2() {
    return 13476220616073LL;
}
