#include <format>
#include <sstream>
#include <numeric>

#include "utils/utils.hpp"

int main() {
    const auto lines = ocb::read_lines("day11/input1.txt");

    std::vector<std::vector<uint64_t> > stones; {
        std::vector<uint64_t> gen0;
        uint64_t stone;
        std::stringstream ss{lines[0]};
        while (ss >> stone) {
            gen0.emplace_back(stone);
        }
        stones.push_back(gen0);
    }

    for (int i = 0; i < 25; ++i) {
        std::vector<uint64_t> gen;
        for (const auto &stone: stones.back()) {
            if (stone == 0) {
                gen.emplace_back(1);
            } else if (const auto stone_str = std::to_string(stone);
                stone_str.size() % 2 == 0) {
                const auto half = stone_str.size() / 2;
                gen.emplace_back(std::atoi(stone_str.substr(0, half).c_str()));
                gen.emplace_back(std::atoi(stone_str.substr(half).c_str()));
            } else {
                gen.emplace_back(stone * 2024);
            }
        }
        stones.push_back(gen);
    }

    std::cout << std::format("Result is: {}", stones.back().size()) << std::endl;
}
