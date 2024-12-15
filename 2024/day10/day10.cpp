#include <format>
#include <ranges>
#include <deque>
#include <numeric>
#include <unordered_set>

#include "utils/utils.hpp"

int main() {
    const auto lines = ocb::read_lines("day10/input1.txt");
    const auto lines_at = [&lines] (const ocb::Position& pos) { return lines.at(pos.row).at(pos.col); };

    std::deque<std::pair<ocb::Position, ocb::Position>> trailheads;

    for (const auto& [row, line] : lines | std::ranges::views::enumerate) {
        for (const auto& [col, c] : line | std::ranges::views::enumerate) {
            if (c == '0') trailheads.emplace_back(ocb::Position{row, col}, ocb::Position{row, col});
        }
    }

    int sum = 0;
    while (!trailheads.empty()) {
        const auto [start, current] = trailheads.front();
        trailheads.pop_front();

        const auto& node_value = lines_at(current);
        if (node_value == '9') {
            ++sum;
            continue;
        }

        const auto next_node_value = node_value + 1;

        try {
            if (const ocb::Position next_node_candidate{current.row-1, current.col};
            lines_at(next_node_candidate) == next_node_value) {
                trailheads.emplace_back(start, next_node_candidate);
            }
        } catch (const std::out_of_range&) {};
        try {
            if (const ocb::Position next_node_candidate{current.row, current.col+1};
            lines_at(next_node_candidate) == next_node_value) {
                trailheads.emplace_back(start, next_node_candidate);
            }
        } catch (const std::out_of_range&) {};
        try {
            if (const ocb::Position next_node_candidate{current.row+1, current.col};
            lines_at(next_node_candidate) == next_node_value) {
                trailheads.emplace_back(start, next_node_candidate);
            }
        } catch (const std::out_of_range&) {};
        try {
            if (const ocb::Position next_node_candidate{current.row, current.col-1};
            lines_at(next_node_candidate) == next_node_value) {
                trailheads.emplace_back(start, next_node_candidate);
            }
        } catch (const std::out_of_range&) {};
    }

    std::cout << std::format("Result is: {}", sum) << std::endl;
}
