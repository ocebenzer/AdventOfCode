#include <format>
#include <ranges>
#include <deque>
#include <numeric>
#include <unordered_map>

#include "utils/utils.hpp"

struct plot {
    int area;
    int perimeter;
};

int main() {
    const auto lines = ocb::read_lines("day12/input1.txt");
    auto garden = lines;

    std::unordered_multimap<char, plot> plots;

    for (int row = 0; row < garden.size(); ++row) {
        for (int col = 0; col < garden[0].size(); ++col) {
            const auto cell = garden[row][col];
            if (cell == '_') continue;

            plot plot{0, 0};

            std::deque<ocb::Position> positions{{row, col}};
            while (!positions.empty()) {
                const auto pos = positions.front();
                positions.pop_front();
                if (garden[pos.row][pos.col] == '_') continue;
                garden[pos.row][pos.col] = '_';

                ++plot.area;

                std::initializer_list<ocb::Position> sides{
                    {pos.row - 1, pos.col}, {pos.row, pos.col + 1}, {pos.row + 1, pos.col}, {pos.row, pos.col - 1}
                };

                for (const auto &side: sides) {
                    try {
                        if (garden.at(side.row).at(side.col) == cell) {
                            positions.emplace_back(side.row, side.col);
                        } else if (lines[side.row][side.col] != cell) {
                            ++plot.perimeter;
                        }
                    } catch (std::out_of_range &) {
                        ++plot.perimeter;
                    }
                }
            }

            plots.emplace(cell, plot);
        }
    }

    int sum = 0;
    for (const auto [crop, plot]: plots) {
        sum += plot.area * plot.perimeter;
    }

    std::cout << std::format("Result is: {}", sum) << std::endl;
}
