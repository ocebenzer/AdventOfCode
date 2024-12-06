#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

int main() {
    std::string s_time{""};
    std::string s_distance{""};
    long ways{0};
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
                ss >> token;
                s_time += token;
            }
        }
        {
            std::getline(file, line);

            std::stringstream ss{line};
            ss >> token;

            for(int i{0}; !ss.eof(); i++) {
                ss >> token;
                s_distance += token;
            }
        }
    }

    {
        long long time{std::atoll(s_time.c_str())};
        long long distance{std::atoll(s_distance.c_str())};
        const auto calculate_distance = [] (long button_hold_time, long travel_time) {
            return button_hold_time * travel_time;
        };

        if (time % 2 == 0) {
            if (calculate_distance(time/2, time/2) > distance) {
                ways++;
            }
            else {
                std::cout << 0 << std::endl;
                exit(0);
            }
        }

        const auto middle{(time-1) / 2};

        auto button_hold_time{middle};
        while (calculate_distance(button_hold_time, time - button_hold_time) > distance) {
            ways += 2;
            button_hold_time--;
        }
    }

    std::cout << ways << std::endl;
}
