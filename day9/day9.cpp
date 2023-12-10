#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include <numeric>

int main() {
    std::vector<std::vector<int>> histories;

    {
        std::ifstream file{"../day9.txt"};
        if (!file.is_open()) {
            std::cout << "file not open" << std::endl;
            exit(1);
        }

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss{line};
            std::vector<int> history;

            while (!ss.eof()) {
                int value;
                ss >> value;
                history.push_back(value);
            }

            histories.push_back(std::move(history));
        }

        file.close();
    }

    long long sum{0};

    for (const auto& history : histories) {
        std::vector<std::vector<int>> diffs;

        diffs.push_back(history);
        std::reverse(diffs.rbegin()->begin(), diffs.rbegin()->end());

        const auto all_zero = [] (const std::vector<int>& list) {
            for (const auto& e : list) {
                if (e != 0) return false;
            }
            return true;
        };

        while (!all_zero(*diffs.rbegin())) {
            const auto& upper_level{*diffs.rbegin()};
            std::vector<int> level;
            for (auto itr{upper_level.rbegin()+1}; itr < upper_level.rend(); ++itr) {
                level.push_back(*itr - *(itr-1));
            }
            diffs.push_back(level);
            std::reverse(diffs.rbegin()->begin(), diffs.rbegin()->end());
        }

        diffs.rbegin()->push_back(0);

        for (auto itr{diffs.rbegin()+1}; itr < diffs.rend(); itr++) {
            const auto upper_last{*(itr-1)->rbegin()};
            const auto last{*itr->rbegin()};
            itr->push_back(last - upper_last);
        }

        sum += *diffs.begin()->rbegin();
    }

    std::cout << sum << std::endl;
}
