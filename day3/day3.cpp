#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

const auto is_digit = [] (const char c) { return c >= '0' && c <= '9'; };
const auto is_symbol = [] (const char c) { return c < '0' && c > '9' || c != '.'; };

int main() {
    std::ifstream file{"../day3.txt"};
    if (!file.is_open()) {
        std::cout << "file not open" << std::endl;
        exit(1);
    }

    std::vector<std::string> lines;
    {
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(std::string("." + line + "."));
        }
    }

    int sum{0};

    for (int row{0}; row < lines.size(); row++) {
        const std::string_view line{lines[row]};
        for (int number_begin{1}; number_begin < line.size(); number_begin++) {
            if (is_digit(line[number_begin-1]) || !is_digit(line[number_begin])) continue;

            int number = std::atoi(&line[number_begin]);

            int number_end{number_begin};
            while (number_end < line.size() && is_digit(line[number_end])) {
                number_end++;
            }

            bool is_part_number = false;

            const auto has_symbol = [] (const std::string_view& line) {
                for (const char c : line) {
                    if (is_symbol(c)) return true;
                }
                return false;
            };

            if (row > 0) {
                const auto upper_line = std::string_view{lines[row-1]};
                const auto upper_line_slice = upper_line.substr(number_begin-1, number_end - number_begin + 2);
                if (has_symbol(upper_line_slice)) {
                    sum += number;
                    continue;
                }
            }

            if (is_symbol(line[number_begin - 1]) || is_symbol(line[number_end])) {
                    sum += number;
                    continue;
            }

            if (row < lines.size()-1) {
                const auto lower_line = std::string_view{lines[row+1]};
                const auto lower_line_slice = lower_line.substr(number_begin-1, number_end - number_begin + 2);
                if (has_symbol(lower_line_slice)) {
                    sum += number;
                    continue;
                }
            }
        }
    }

    std::cout << sum << std::endl;
}