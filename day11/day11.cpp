#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

using pos = std::pair<int, int>;

int main() {
    std::vector<std::string> map;
    std::vector<int> empty_rows;
    std::vector<int> empty_cols;

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
                empty_rows.push_back(map.size()-1);
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
            empty_cols.push_back(col);
        }
    }

    std::sort(empty_rows.begin(), empty_rows.end());
    std::sort(empty_cols.begin(), empty_cols.end());

    long sum{0};
    const int empty_factor{1000000-1};

    for (int i{0}; i < galaxies.size(); ++i) {
        for (int j{i+1}; j < galaxies.size(); ++j) {
            const auto& [r1, c1] {galaxies[i]};
            const auto& [r2, c2] {galaxies[j]};
            sum += std::abs(r1 - r2);
            sum += std::abs(c1 - c2);
            {
                const auto itr1{std::find_if(empty_rows.begin(), empty_rows.end(), [r1] (const int row) { return row >= r1; })};
                const auto itr2{std::find_if(empty_rows.begin(), empty_rows.end(), [r2] (const int row) { return row >= r2; })};
                sum += std::abs(std::distance(itr2, itr1)) * empty_factor;
            }
            {
                const auto itr1{std::find_if(empty_cols.begin(), empty_cols.end(), [c1] (const int col) { return col >= c1; })};
                const auto itr2{std::find_if(empty_cols.begin(), empty_cols.end(), [c2] (const int col) { return col >= c2; })};
                sum += std::abs(std::distance(itr2, itr1)) * empty_factor;
            }
        }
    }

    std::cout << sum << std::endl;
}
