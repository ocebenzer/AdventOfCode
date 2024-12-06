#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>

using pos = std::pair<int, int>;
using node = std::pair<char, int>;

int main() {
    std::vector<std::vector<node>> map;
    std::vector<std::vector<char>> spread_map;
    pos start{-1, -1};

    {
        std::ifstream file{"../day10.txt"};
        if (!file.is_open()) {
            std::cout << "file not open" << std::endl;
            exit(1);
        }

        std::string line;
        while (std::getline(file, line)) {
            const int i{static_cast<int>(map.size())};
            std::vector<node> row;
            row.reserve(line.size());
            for (auto j{0}; j < line.size(); ++j) {
                const char c{line[j]};
                row.push_back({c, -1});
                if (c == 'S') {
                    start = {i, j};
                }
            }
            map.push_back(row);
            spread_map.push_back(std::vector<char>(line.size(), '.'));
        }

        file.close();
    }

    pos curr{start};
    pos prev{start};
    int max{0};

    const auto find_neighbors = [&map] (const int i, const int j) {
        std::array<pos, 2> neighbors;
        int index{0};

        // i hate this
        if (i > 0 && std::string{"|7F"}.find(map[i-1][j].first) != std::string::npos) {
            neighbors[index++] = {i-1, j};
        }
        if (i < map.size()-1 && std::string{"|LJ"}.find(map[i+1][j].first) != std::string::npos)  {
            neighbors[index++] = {i+1, j};
        }
        if (j > 0 && std::string{"-LF"}.find(map[i][j-1].first) != std::string::npos) {
            neighbors[index++] = {i, j-1};
        }
        if (j < map.begin()->size()-1 && std::string{"-J7"}.find(map[i][j+1].first) != std::string::npos) {
            neighbors[index++] = {i, j+1};
        }
        
        return neighbors;
    };

    do {
        auto& [i, j] {curr};
        auto& [c, dist] {map[i][j]};

        std::array<pos, 2> neighbors;

        const std::pair up{i-1, j};
        const std::pair down{i+1, j};
        const std::pair left{i, j-1};
        const std::pair right{i, j+1};

        pos next;

        switch (c) {
            case '|':
                neighbors = {up, down};
                break;
            case '-':
                neighbors = {left, right};
                break;
            case 'L':
                neighbors = {up, right};
                break;
            case 'S':
                neighbors = find_neighbors(i, j);
                if (neighbors[0] == up && neighbors[1] == down) { c = '|'; };
                if (neighbors[0] == left && neighbors[1] == right) { c = '-'; };
                if (neighbors[0] == up && neighbors[1] == right) { c = 'L'; };
                if (neighbors[0] == up && neighbors[1] == left) { c = 'J'; };
                if (neighbors[0] == down && neighbors[1] == left) { c = '7'; };
                if (neighbors[0] == down && neighbors[1] == right) { c = 'F'; };
                break;
            case 'J':
                neighbors = {up, left};
                break;
            case '7':
                neighbors = {down, left};
                break;
            case 'F':
                neighbors = {down, right};
                break;
            case '.':
            default:
                throw std::invalid_argument("");
        }

        if (neighbors[0] == prev) {
            next = neighbors[1];
        }
        else {
            next = neighbors[0];
        }

        prev = curr;
        curr = next;

        max++;

        spread_map[curr.first][curr.second] = map[curr.first][curr.second].first;
    } while (curr != start);

    int ctr{0};

    for (int i{0}; i < spread_map.size(); ++i) {
        for (int j{0}; j < spread_map[0].size(); ++j) {
            const char c{spread_map[i][j]};
            if (c != '.') continue;

            int wall_points{0};
            for (int k{j}; k >=0; --k) {
                const char c_left{spread_map[i][k]};
                if (c_left == '|') {
                    wall_points += 2;
                }
                if (std::string{"JF"}.find(c_left) != std::string::npos) {
                    wall_points += 1;
                }
                if (std::string{"L7"}.find(c_left) != std::string::npos) {
                    wall_points -= 1;
                }
            }
            if (wall_points % 4 != 0) {
                ++ctr;
            }
        }
    }

    std::cout << ctr << std::endl;
}
