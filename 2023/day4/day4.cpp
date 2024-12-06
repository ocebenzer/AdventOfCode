#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>
#include <numeric>


int main() {
    std::ifstream file{"../day4.txt"};
    if (!file.is_open()) {
        std::cout << "file not open" << std::endl;
        exit(1);
    }

    // Card numbers start from 1
    std::vector<int> n_card_copies;

    int current_card{0};
    while(!file.eof()) { // careful, no extra line should be in input
        current_card++;

        if (n_card_copies.size() < current_card) {
            n_card_copies.push_back(0);
        }

        std::array<int, 10> win_numbers;

        std::string tmp;

        // Card #:
        file >> tmp >> tmp;

        for (int i{0}; i < 10; i++) {
            file >> win_numbers[i];
        }

        // |
        file >> tmp;

        int matches{0};

        int number{0};
        for (int i{0}; i < 25; i++) {
            file >> number;
            if (std::find(win_numbers.begin(), win_numbers.end(), number) != win_numbers.end()) {
                matches++;
            }
        }
        const int n_current_cards{n_card_copies[current_card-1] + 1};

        // std::cout << "Card " << current_card << ": " << matches << " matches. (x" << n_current_cards << ")\n";

        for (int i{current_card-1 + 1}; i <= current_card-1 + matches; i++) {
            try {
                n_card_copies.at(i) += n_current_cards;
            }
            catch (std::out_of_range e) {
                n_card_copies.push_back(n_current_cards);
            }
        }
    }

    const int total_copies{std::reduce(n_card_copies.begin(), n_card_copies.end(), 0, [] (int a, int b) { return a + b; })};

    std::cout << n_card_copies.size() + total_copies << std::endl;
}
