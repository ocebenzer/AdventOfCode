#include <regex>

#include "utils.h"

int main() {
    const auto lines = ocb::read_lines("day4/input1.txt");


    int counter = 0;
    for (int row = 0; row < lines.size(); row++) {
        for (int col = 0; col < lines.size(); col++) {
            const auto& x = lines[row][col];
            if (x != 'X') continue;

            try {
                const auto& m = lines.at(row).at(col+1);
                const auto& a = lines.at(row).at(col+2);
                const auto& s = lines.at(row).at(col+3);
                if (m == 'M' && a == 'A' && s == 'S') counter++;
            } catch (const std::out_of_range& e) { }
            try {
                const auto& m = lines.at(row+1).at(col+1);
                const auto& a = lines.at(row+2).at(col+2);
                const auto& s = lines.at(row+3).at(col+3);
                if (m == 'M' && a == 'A' && s == 'S') counter++;
            } catch (const std::out_of_range& e) { }
            try {
                const auto& m = lines.at(row+1).at(col);
                const auto& a = lines.at(row+2).at(col);
                const auto& s = lines.at(row+3).at(col);
                if (m == 'M' && a == 'A' && s == 'S') counter++;
            } catch (const std::out_of_range& e) { }
            try {
                const auto& m = lines.at(row+1).at(col-1);
                const auto& a = lines.at(row+2).at(col-2);
                const auto& s = lines.at(row+3).at(col-3);
                if (m == 'M' && a == 'A' && s == 'S') counter++;
            } catch (const std::out_of_range& e) { }
            try {
                const auto& m = lines.at(row).at(col-1);
                const auto& a = lines.at(row).at(col-2);
                const auto& s = lines.at(row).at(col-3);
                if (m == 'M' && a == 'A' && s == 'S') counter++;
            } catch (const std::out_of_range& e) { }
            try {
                const auto& m = lines.at(row-1).at(col-1);
                const auto& a = lines.at(row-2).at(col-2);
                const auto& s = lines.at(row-3).at(col-3);
                if (m == 'M' && a == 'A' && s == 'S') counter++;
            } catch (const std::out_of_range& e) { }
            try {
                const auto& m = lines.at(row-1).at(col);
                const auto& a = lines.at(row-2).at(col);
                const auto& s = lines.at(row-3).at(col);
                if (m == 'M' && a == 'A' && s == 'S') counter++;
            } catch (const std::out_of_range& e) { }
            try {
                const auto& m = lines.at(row-1).at(col+1);
                const auto& a = lines.at(row-2).at(col+2);
                const auto& s = lines.at(row-3).at(col+3);
                if (m == 'M' && a == 'A' && s == 'S') counter++;
            } catch (const std::out_of_range& e) { }
        }
    }

    std::cout << counter << std::endl;
}
