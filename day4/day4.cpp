#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <array>


int main() {
    std::ifstream file{"../day4.txt"};
    if (!file.is_open()) {
        std::cout << "file not open" << std::endl;
        exit(1);
    }

    int points{0};

    while(!file.eof()) {
        std::array<int, 10> win_numbers;

        std::string tmp;

        // Card #:
        file >> tmp >> tmp;

        for (int i{0}; i < 10; i++) {
            file >> win_numbers[i];
        }

        // |
        file >> tmp;

        int line_point{1};

        int number{0};
        for (int i{0}; i < 25; i++) {
            file >> number;
            if (std::find(win_numbers.begin(), win_numbers.end(), number) != win_numbers.end()) {
                line_point *= 2;
            }
        }

        points += line_point / 2;
    }

    std::cout << points << std::endl;
}