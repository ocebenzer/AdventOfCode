#include <regex>

#include "utils/utils.hpp"

int main() {
    const auto lines = ocb::read_lines("day4/input1.txt");


    int counter = 0;
    for (int row = 0; row < lines.size(); row++) {
        for (int col = 0; col < lines.size(); col++) {
            const auto& x = lines[row][col];
            if (x != 'A') continue;

            try {
                const auto& m1 = lines.at(row-1).at(col-1);
                const auto& s1 = lines.at(row+1).at(col+1);
                const auto& m2 = lines.at(row+1).at(col-1);
                const auto& s2 = lines.at(row-1).at(col+1);
                if (m1 == 'M' && m2 == 'M' && s1 == 'S' && s2 == 'S') counter++;
            } catch (const std::out_of_range& e) { }
            try {
                const auto& m1 = lines.at(row+1).at(col+1);
                const auto& s1 = lines.at(row-1).at(col-1);
                const auto& m2 = lines.at(row+1).at(col-1);
                const auto& s2 = lines.at(row-1).at(col+1);
                if (m1 == 'M' && m2 == 'M' && s1 == 'S' && s2 == 'S') counter++;
            } catch (const std::out_of_range& e) { }
            try {
                const auto& m1 = lines.at(row-1).at(col-1);
                const auto& s1 = lines.at(row+1).at(col+1);
                const auto& m2 = lines.at(row-1).at(col+1);
                const auto& s2 = lines.at(row+1).at(col-1);
                if (m1 == 'M' && m2 == 'M' && s1 == 'S' && s2 == 'S') counter++;
            } catch (const std::out_of_range& e) { }
            try {
                const auto& m1 = lines.at(row+1).at(col+1);
                const auto& s1 = lines.at(row-1).at(col-1);
                const auto& m2 = lines.at(row-1).at(col+1);
                const auto& s2 = lines.at(row+1).at(col-1);
                if (m1 == 'M' && m2 == 'M' && s1 == 'S' && s2 == 'S') counter++;
            } catch (const std::out_of_range& e) { }
        }
    }

    std::cout << counter << std::endl;
}
