#include <ranges>
#include <numeric>
#include <iterator>
#include <format>
#include "utils/utils.hpp"

int main() {
    const auto lines = ocb::read_lines("day9/input1.txt");

    const auto size = std::accumulate(lines[0].begin(), lines[0].end(), 0ULL);
    std::vector<long long> blocks;
    blocks.reserve(size);

    for (const auto& [index, c] : lines[0] | std::ranges::views::enumerate) {
        const auto block_id = index % 2 == 0 ? index/2 : -1;
        blocks.insert(blocks.end(), c - '0', block_id);
    }

    for (auto forward = blocks.begin(), backward = blocks.end()-1;;) {
        while (*forward != -1) ++forward;
        while (*backward == -1) --backward;
        if (forward > backward) break;

        *forward = *backward;
        *backward = -1;
    }

    auto sum = 0ull;
    for (const auto& [index, c] : blocks | std::ranges::views::enumerate) {
        if (c == -1) break;
        sum += index * c;
    }

    std::cout << std::format("Result is: {}", sum) << std::endl;
}
