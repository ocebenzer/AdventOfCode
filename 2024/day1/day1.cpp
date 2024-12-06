#include <numeric>

#include "utils.h"
#include <ranges>

int main() {
    const auto lines = ocb::read_lines("day1/input1.txt");

    std::vector<int> lefts, rights;
    for (const auto& line : lines) {
        std::stringstream ss(line);
        int left, right;
        ss >> left >> right;
        lefts.push_back(left);
        rights.push_back(right);
    }

    std::ranges::sort(lefts);
    std::ranges::sort(rights);

    std::vector<int> result;
    for (int i = 0; i < lefts.size(); ++i) { // std::ranges::zip_view my beloved
        const auto& left = lefts[i];
        const auto& right = rights[i];
        result.push_back(std::abs(left - right));
    }

    const auto sum = std::accumulate(result.begin(), result.end(), 0);
    std::cout << sum << std::endl;

}
