#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>

using pos = std::pair<int, int>;

int main() {
    std::vector<std::string> map;

    {
        std::ifstream file{"../day11.txt"};
        if (!file.is_open()) {
            std::cout << "file not open" << std::endl;
            exit(1);
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;

            map.push_back(line);
            if (line.find_first_not_of('.') == std::string::npos) {
                map.push_back(line);
            }
        }

        file.close();
    }

    std::vector<pos> galaxies;

    for (int col{0}; col < map.begin()->size(); ++col) {
        bool is_col_empty{true};

        for (int row{0}; row < map.size(); ++row) {
            const char c{map[row][col]};
            if (c != '.') {
                is_col_empty = false;
                galaxies.push_back({row, col});
            }
        }

        if (is_col_empty) {
            for (auto& line : map) {
                line.insert(line.begin()+col, '.');
            }
            ++col;
            continue;
        }
    }

    int sum{0};

    for (int i{0}; i < galaxies.size(); ++i) {
        for (int j{i}; j < galaxies.size(); ++j) {
            const auto& [r1, c1] {galaxies[i]};
            const auto& [r2, c2] {galaxies[j]};
            sum += std::abs(r1 - r2);
            sum += std::abs(c1 - c2);
        }
    }

    std::cout << sum << std::endl;
}
