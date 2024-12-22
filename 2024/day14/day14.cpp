#include <format>
#include <iostream>
#include "utils/utils.hpp"
#include "md/vector2.hpp"

constexpr ocb::vector2 grid_size{101, 103};
constexpr auto seconds{100};

constexpr auto find_quadrant = [] (auto& position) {
    const auto half = grid_size / 2;
    if (position[0] < half[0] && position[1] < half[1]) return 0;
    if (position[0] > half[0] && position[1] < half[1]) return 1;
    if (position[0] < half[0] && position[1] > half[1]) return 2;
    if (position[0] > half[0] && position[1] > half[1]) return 3;
    return -1;
};

int main() {
    const auto lines = ocb::read_lines("day14/input0.txt");

    std::vector<std::tuple<ocb::vector2<>, ocb::vector2<>, ocb::vector2<>>> data;
    for (const auto& line : lines) {
        ocb::vector2 initial_position, velocity;
        std::sscanf(line.c_str(), "p=%d,%d v=%d,%d", &initial_position[0], &initial_position[1], &velocity[0], &velocity[1]);

        const auto position = initial_position;
        data.emplace_back(initial_position, velocity, position);
    }

    std::array<int, 4> quadrants{};
    for (auto& [initial, velocity, position] : data) {
        position += ((velocity + grid_size) * seconds);
        position %= grid_size;

        const auto quadrant = find_quadrant(position);
        if (quadrant < 0) continue;

        ++quadrants[quadrant];
    }

    const auto result = std::accumulate(quadrants.begin(), quadrants.end(), 1, std::multiplies());

    std::cout << std::format("Result is: {}", result) << std::endl;
}
