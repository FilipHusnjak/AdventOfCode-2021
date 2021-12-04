#include <iostream>
#include <vector>

int first_part(const std::vector<int> &depths) {
    int count = 0;
    for (int i = 1; i < depths.size(); i++)
        count += depths[i] > depths[i - 1];
    return count;
}

int second_part(const std::vector<int> &depths) {
    int count = 0;
    for (int i = 3; i < depths.size(); i++)
        count += depths[i] > depths[i - 3];
    return count;
}

int main() {
    std::vector<int> depths;
    for (int depth; std::cin >> depth;)
        depths.push_back(depth);

    std::cout << "First part: " << first_part(depths) << std::endl;
    std::cout << "Second part: " << second_part(depths) << std::endl;

    return 0;
}
