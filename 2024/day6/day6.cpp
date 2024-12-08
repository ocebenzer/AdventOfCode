#include <span>

#include "utils/utils.hpp"

struct position { int row; int col; };
constexpr position DIRECTIONS[] = {
    {-1, 0}, {0, 1}, { 1, 0}, {0, -1}
};
enum direction { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3 };

position find_pos(const std::span<std::string> lines) {
    for (int row = 0; row < lines.size(); row++) {
        for (int col = 0; col < lines[row].size(); col++) {
            if (lines[row][col] == '^') return {row, col};
        }
    }
    throw std::invalid_argument("no ^");
}

int main() {
    auto lines = ocb::read_lines("day6/input1.txt");

    auto pos = find_pos(lines);
    int direction = UP;

    while (true) {
        auto& current = lines[pos.row][pos.col];
        auto directon_vector = DIRECTIONS[direction];
        position target_pos = {pos.row + directon_vector.row, pos.col +directon_vector.col};
        if (target_pos.row < 0 || target_pos.row >= lines.size() || target_pos.col < 0 || target_pos.col >= lines.size()) {
            current = 'X';
            break;
        }

        auto& target = lines[target_pos.row][target_pos.col];
        if (target == '#') {
            direction = (direction+1) % 4;
            continue;
        }

        current = 'X';
        target = '^';
        pos = target_pos;
    }


    int sum = 0;
    for (const auto& line : lines) {
        for (const auto& c : line) {
            if (c == 'X') ++sum;
        }
    }
    std::cout << sum << std::endl;
}
