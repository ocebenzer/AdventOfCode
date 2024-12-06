#include <numeric>

#include "utils.h"
#include <ranges>
#include <unordered_map>

bool is_safe (std::span<const int> levels) {
    bool is_ascending = true;
    bool is_descending = true;
    bool is_adjacent_valid = true;

    auto prev_level = *levels.begin();
    for (const auto& level : std::span{levels.begin()+1, levels.end()}) {
        is_ascending &= prev_level > level;
        is_descending &= prev_level < level;
        is_adjacent_valid &= std::abs(prev_level - level) <= 3;


        if (!is_adjacent_valid) return false;
        if (!is_ascending && !is_descending) return false;
        prev_level = level;
    }

    return true;
}

int main() {
    const auto lines = ocb::read_lines("day2/input1.txt");

    std::vector<std::vector<int>> reports;
    std::ranges::for_each(lines, [&reports](auto &line) {
        std::vector<int> report;
        std::stringstream ss(line);
        for (int level; ss >> level;) {
            report.push_back(level);
        }
        reports.emplace_back(report);
    });

    int safe_counter = 0;
    for (const auto& levels : reports) {
        if (is_safe(std::span{levels.begin(), levels.end()})) ++safe_counter;
    }

    std::cout << safe_counter << std::endl;
}
