#include <format>
#include "utils/utils.hpp"

int main() {
    const auto lines = ocb::read_lines("day13/input1.txt");

    std::vector<std::tuple<ocb::Position, ocb::Position, ocb::Position, std::vector<std::pair<int, int> > > > machines;
    for (int i = 0; i < lines.size(); i += 4) {
        std::string word;
        char c;
        ocb::Position buttonA, buttonB, prize; {
            std::stringstream ss(lines[i]);
            ss >> word >> word >> c >> c >> buttonA.col >> word >> c >> c >> buttonA.row;
        } {
            std::stringstream ss(lines[i + 1]);
            ss >> word >> word >> c >> c >> buttonB.col >> word >> c >> c >> buttonB.row;
        } {
            std::stringstream ss(lines[i + 2]);
            ss >> word >> c >> c >> prize.col >> word >> c >> c >> prize.row;
        }

        machines.emplace_back(buttonA, buttonB, prize, std::vector<std::pair<int, int> >{});
    }


    for (auto &[buttonA, buttonB, prize, amount]: machines) {
        for (int buttonAAmount = 0; buttonAAmount <= 100; ++buttonAAmount) {
            for (int buttonBAmount = 0; buttonBAmount <= 100; ++buttonBAmount) {
                if (buttonA.row * buttonAAmount + buttonB.row * buttonBAmount == prize.row && buttonA.col *
                    buttonAAmount + buttonB.col * buttonBAmount == prize.col) {
                    amount.emplace_back(buttonAAmount, buttonBAmount);
                }
            }
        }
    }

    int sum = 0;
    for (auto &[buttonA, buttonB, prize, amount]: machines) {
        if (amount.empty()) continue;
        std::sort(amount.begin(), amount.end(), [](auto &a, auto &b) {
            return a.first * 3 + a.second < b.first * 3 + b.second;
        });
        if (amount.size() > 1) {
            std::cout << std::endl;
        }
        sum += amount[0].first * 3 + amount[0].second;
    }

    std::cout << std::format("Result is: {}", sum) << std::endl;
}
