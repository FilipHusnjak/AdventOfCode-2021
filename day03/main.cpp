#include <iostream>
#include <vector>
#include <list>
#include <functional>
#include <string>

auto first_part(const std::vector<std::string> &inputs) {
    std::vector<int> counts(inputs[0].size(), 0);
    for (const auto &input: inputs)
        for (int j = 0; j < input.size(); j++)
            counts[j] += input[j] == '1';
    long res = 0;
    for (size_t half = inputs.size() >> 1; int count: counts)
        res = (res + (count > half)) << 1;
    res >>= 1;
    return res * (res ^ ((long) std::pow(2, counts.size()) - 1));
}

auto get_rating(const std::vector<std::string> &inputs, const std::function<bool(int, int)>& f) {
    if (inputs.empty()) return 0L;
    std::list<std::string> result(inputs.begin(), inputs.end());
    for (int bit = 0; result.size() > 1 && bit < inputs[0].size(); bit++) {
        int count = 0;
        for (const auto &r: result)
            count += r[bit] == '0';
        char c = f(count, (int)result.size() / 2) ? '1' : '0';
        for (auto it = result.begin(); it != result.end();) {
            if ((*it)[bit] != c) it = result.erase(it);
            else it++;
        }
    }
    if (result.empty()) return 0L;
    return std::stol(*result.begin(), nullptr, 2);
}

auto second_part(const std::vector<std::string> &inputs) {
    return get_rating(inputs, std::less_equal<>()) * get_rating(inputs, std::greater<>());
}

int main() {
    std::vector<std::string> inputs;
    std::string binary;
    while (std::cin >> binary)
        inputs.push_back(binary);

    std::cout << "First part: " << first_part(inputs) << std::endl;
    std::cout << "Second part: " << second_part(inputs) << std::endl;

    return 0;
}
