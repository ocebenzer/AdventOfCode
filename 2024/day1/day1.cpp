#include <numeric>

#include "utils.h"
#include <ranges>
#include <unordered_map>

int main() {
    const auto lines = ocb::read_lines("day1/input1.txt");

    std::vector<int> lefts;
    std::unordered_map<int, int> rights;
    for (const auto& line : lines) {
        std::stringstream ss(line);
        int left, right;
        ss >> left >> right;
        lefts.push_back(left);

        if (rights.contains(right)) {
            ++rights[right];
        }
        else {
            rights[right] = 1;
        }
    }

    std::ranges::sort(lefts);

    std::vector<int> result;
    for (const auto& left : lefts) { // std::ranges::zip_view my beloved
        result.push_back(left * rights[left]);
    }

    const auto sum = std::accumulate(result.begin(), result.end(), 0);
    std::cout << sum << std::endl;

}
