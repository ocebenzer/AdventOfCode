#include <set>
#include <unordered_map>
#include <unordered_set>

#include "utils.h"

int main() {
    const auto lines = ocb::read_lines("day8/input1.txt");

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


    std::unordered_map<char, std::vector<ocb::Position>> antinode_lists;
    for (const auto& [c, node_list] : node_lists) {
        for (auto i = 0; i < node_list.size(); ++i) {
            for (int j = 0; j < node_list.size(); ++j) {
                if (j == i) continue;

                const auto& node1 = node_list[i];
                const auto& node2 = node_list[j];

                const ocb::Position antinode{
                    node2.row + (node2.row - node1.row),
                    node2.col + (node2.col - node1.col),
                };

                if (antinode_lists.contains(c)) {
                    auto& antinode_list = antinode_lists[c];
                    antinode_list.push_back(antinode);
                }
                else {
                    std::vector<ocb::Position> antinode_list;
                    antinode_list.emplace_back(antinode);
                    antinode_lists.emplace(c, antinode_list);
                }

            }
        }
    }

    std::unordered_set<ocb::Position> unique_antinodes;
    for (const auto& [c, node_list] : antinode_lists) {
        for (const auto& node : node_list) {
            unique_antinodes.insert(node);
        }
    }

    const auto sum = std::ranges::count_if(unique_antinodes, [&lines] (const auto& node) {
        return node.col >= 0 && node.col < lines.size() &&
            node.row >= 0 && node.row < lines[0].size();
    });

    std::cout << sum << std::endl;
}
