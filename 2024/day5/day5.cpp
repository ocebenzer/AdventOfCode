#include <unordered_map>
#include <span>

#include "utils.h"

bool update_valid (std::unordered_map<int, std::vector<int>>& rules, const std::span<const int> pages) {
    for (auto page = pages.begin(); page < pages.end(); ++page) {
        if (!rules.contains(*page)) continue;

        for (const auto& rule : rules[*page]) {
            auto target_page = std::ranges::find(pages, rule);
            if (std::distance(page, target_page) < 0) return false;
        }
    }

    return true;
}

int main() {
    const auto lines = ocb::read_lines("day5/input1.txt");

    std::unordered_map<int, std::vector<int>> rules;
    std::vector<std::vector<int>> updates;

    bool is_rules_done = false;
    for (const auto& line : lines) {
        if (line.empty()) {
            is_rules_done = true;
        }
        else if (!is_rules_done) {
            int num1, num2;
            char c;
            std::stringstream ss(line);
            ss >> num1 >> c >> num2;
            if (rules.contains(num1)) {
                rules[num1].push_back(num2);
            }
            else {
                rules[num1] = std::vector{num2};
            }
        }
        else {
            std::vector<int> pages;
            int num;
            char c;
            std::stringstream ss(line);
            while (!ss.eof()) {
                ss >> num >> c;
                pages.push_back(num);
            }
            updates.push_back(pages);
        }
    }

    int sum = 0;
    for (const auto& pages : updates) {
        if (update_valid(rules, std::span{pages.begin(), pages.end()})) {
            sum += pages[pages.size() / 2 ];
        }
    }

    std::cout << sum << std::endl;
}
