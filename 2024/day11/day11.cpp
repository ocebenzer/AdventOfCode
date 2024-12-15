#include <format>
#include <sstream>
#include <map>

#include "utils/utils.hpp"

constexpr auto increment = [](auto &map, const auto &key, const ocb::BigInt &times = 1) {
    if (map.contains(key)) map[key] += times;
    else map[key] = times;
};

int main() {
    const auto lines = ocb::read_lines("day11/input1.txt");

    std::vector<std::map<uint64_t, ocb::BigInt> > stones; {
        std::map<uint64_t, ocb::BigInt> gen0;
        uint64_t stone;
        std::stringstream ss{lines[0]};
        while (ss >> stone) {
            increment(gen0, stone);
        }
        stones.push_back(gen0);
    }

    for (int i = 0; i < 75; ++i) {
        std::map<uint64_t, ocb::BigInt> gen;
        for (const auto &[stone, times]: stones.back()) {
            if (stone == 0) {
                increment(gen, 1, times);
            } else if (std::to_string(stone).size() % 2 == 0) {
                const auto half = std::to_string(stone).size() / 2;
                increment(gen, std::stoull(std::to_string(stone).substr(0, half)), times);
                increment(gen, std::stoull(std::to_string(stone).substr(half)), times);
            } else {
                increment(gen, stone * 2024, times);
            }
        }
        stones.push_back(gen);
        std::cout << i << std::endl;
    }

    ocb::BigInt sum = 0;
    for (const auto &[stone, times]: stones.back()) {
        sum += times;
    }
    std::cout << std::format("Result is: {}", sum.get_value()) << std::endl;
}
