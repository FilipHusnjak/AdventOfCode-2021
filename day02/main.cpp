#include <iostream>
#include <vector>

auto &operator+=(std::pair<long, long> &left, const std::pair<long, long> &right) {
    left.first += right.first;
    left.second += right.second;
    return left;
}

auto first_part(const std::vector<std::pair<long, long>> &input) {
    std::pair<long, long> result;
    for (const auto &i: input)
        result += i;
    return result.first * result.second;
}

auto second_part(const std::vector<std::pair<long, long>> &input) {
    std::pair<long, long> result;
    for (long aim = 0; const auto &i: input)
        result += {i.first, (aim += i.second) * i.first};
    return result.first * result.second;
}

int main() {
    std::string command;
    long amount;
    std::vector<std::pair<long, long>> input;
    while (std::cin >> command >> amount) {
        if (command == "forward") input.emplace_back(amount, 0);
        else if (command == "down") input.emplace_back(0, amount);
        else input.emplace_back(0, -amount);
    }

    std::cout << "First part: " << first_part(input) << std::endl;
    std::cout << "Second part: " << second_part(input) << std::endl;

    return 0;
}
