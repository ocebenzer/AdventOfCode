#include <set>
#include <unordered_map>
#include <unordered_set>

#include "utils.h"

int main() {
    const auto lines = ocb::read_lines("day8/input1.txt");

    const auto in_grid = [&lines] (const auto node) {
        return node.col >= 0 && node.col < lines.size() &&
            node.row >= 0 && node.row < lines[0].size();
    };

    std::unordered_map<char, std::vector<ocb::Position>> node_lists;

    for (int row = 0; row < lines.size(); row++) {
        for (int col = 0; col < lines[row].size(); col++) {
            const auto& c = lines[row][col];
            if (c != '.') {
                if (node_lists.contains(c)) {
                    auto& node_list = node_lists[c];
                    node_list.emplace_back(row, col);
                }
                else {
                    std::vector<ocb::Position> node_list;
                    node_list.emplace_back(row, col);
                    node_lists.emplace(c, node_list);
                }
            }
        }
    }

    std::unordered_set<ocb::Position> unique_antinodes;
    for (const auto& [antenna, node_list] : node_lists) {
        auto lines_copy = lines;
        for (auto i = 0; i < node_list.size(); ++i) {
            for (int j = 0; j < node_list.size(); ++j) {
                if (j == i) continue;

                const auto& node1 = node_list[i];
                const auto& node2 = node_list[j];

                const ocb::Position antinode_vector{
                    (node2.row - node1.row),
                    (node2.col - node1.col),
                };

                for (auto antinode = node2; in_grid(antinode); antinode += antinode_vector) {
                    lines_copy[antinode.row][antinode.col] = '#';
                }
            }
        }
        for (int row = 0; row < lines_copy.size(); row++) {
            for (int col = 0; col < lines_copy[row].size(); col++) {
                const auto& c = lines_copy[row][col];
                if (c == '#') {
                    unique_antinodes.emplace(row, col);
                }
            }
        }
    }

    const auto sum = std::ranges::count_if(unique_antinodes, [&lines] (const auto& node) {
        return node.col >= 0 && node.col < lines.size() &&
            node.row >= 0 && node.row < lines[0].size();
    });

    std::cout << sum << std::endl;
}
