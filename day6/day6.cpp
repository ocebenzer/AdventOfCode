#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <numeric>

int main() {
    std::vector<std::pair<int, int>> races;
    std::vector<long> ways;
    {
        std::ifstream file{"../day6.txt"};
        if (!file.is_open()) {
            std::cout << "file not open" << std::endl;
            exit(1);
        }

        std::string line;
        std::string token;
        {
            std::getline(file, line);

            std::stringstream ss{line};
            ss >> token;

            while(!ss.eof()) {
                long time;
                ss >> time;
                races.push_back(std::make_pair(time, 0));
            }
        }
        {
            std::getline(file, line);

            std::stringstream ss{line};
            ss >> token;

            for(int i{0}; !ss.eof(); i++) {
                long distance;
                ss >> distance;
                races[i].second = distance;
            }
        }
    }

    for (const auto& [time, distance] : races) {
        const auto calculate_distance = [] (long button_hold_time, long travel_time) {
            return button_hold_time * travel_time;
        };

        long ctr{0};

        if (time % 2 == 0) {
            if (calculate_distance(time/2, time/2) > distance) {
                ctr++;
            }
            else {
                ways.push_back(0);
                continue;
            }
        }

        const long middle{(time-1) / 2};

        long button_hold_time{middle};
        while (calculate_distance(button_hold_time, time - button_hold_time) > distance) {
            ctr += 2;
            button_hold_time--;
        }

        ways.push_back(ctr);
    }

    std::cout << std::reduce(ways.begin(), ways.end(), 1, [] (long a, long b) { return a*b; }) << std::endl;
}
