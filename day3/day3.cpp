#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

const auto is_digit = [] (const char c) { return c >= '0' && c <= '9'; };
const auto is_symbol = [] (const char c) { return c < '0' && c > '9' || c != '.'; };
const auto is_gear = [] (const char c) { return c == '*'; };

struct number {
    int row;
    int col;
    int value;
};

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
        for (int col{0}; col < line.size(); col++) {
            if (!is_gear(line[col])) continue;

            const auto get_number = [] (const std::string_view& line, int row, int col) {
                if (!is_digit(line[col])) {
                    return number{row, col, -1};
                }
                while (is_digit(line[col])) {
                    col--;
                }
                return number{row, col+1, std::atoi(&line[col+1])};
            };

            std::vector<number> numbers;

            if (row > 0) {
                const auto upper_line = std::string_view{lines[row-1]};
                
                numbers.push_back(get_number(upper_line, row-1, col-1));
                numbers.push_back(get_number(upper_line, row-1, col));
                numbers.push_back(get_number(upper_line, row-1, col+1));
            }

            numbers.push_back(get_number(line, row, col-1));
            numbers.push_back(get_number(line, row, col+1));

            if (row < lines.size()-1) {
                const auto lower_line = std::string_view{lines[row+1]};

                numbers.push_back(get_number(lower_line, row+1, col-1));
                numbers.push_back(get_number(lower_line, row+1, col));
                numbers.push_back(get_number(lower_line, row+1, col+1));
            }

            int n_numbers = std::erase_if(numbers, [] (const number& n) { return n.value == -1; });

            const auto& n1 = numbers[0];
            for (const auto& n2 : numbers) {
                if (n1.row != n2.row || n1.col != n2.col) {
                    sum += n1.value * n2.value;
                    break;
                }
            }
        }
    }

    std::cout << sum << std::endl;
}