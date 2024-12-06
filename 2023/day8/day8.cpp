#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include <numeric>

struct node {
    std::string id;
    std::string L;
    std::string R;

    std::string get(char c) const {
        switch (c) {
            case 'L':
                return L;
            case 'R':
                return R;
            default:
                throw std::invalid_argument("");
        }
    }
};


int main() {
    std::unordered_map<std::string, node> nodes;
    std::string rule;

    {
        std::ifstream file{"../day8.txt"};
        if (!file.is_open()) {
            std::cout << "file not open" << std::endl;
            exit(1);
        }

        file >> rule;

        while(!file.eof()) {
            std::string id;
            std::string R;
            std::string L;

            file >> id ;

            if (id.empty()) continue;

            {
                std::string token;
                file >> token >> token;
                L = token.substr(1, 3);
                file >> token;
                R = token.substr(0, 3);
            }

            nodes.insert(std::make_pair(id, node{id, L, R}));
        }
    }

    std::vector<std::pair<std::string, int>> current;
    std::transform(nodes.begin(), nodes.end(), std::back_inserter(current), [] (const auto& n) {
        const auto& [key, val]{n};
        return std::make_pair(val.id, 0);
    });
    std::erase_if(current, [] (const auto& n) {
        const auto& [id, i]{n};
        return *id.rbegin() != 'A';
    });

    for (auto& [id, i] : current) {
        while (*id.rbegin() != 'Z') {
            const char c{rule[i % rule.size()]};
            id = nodes[id].get(c);
            i++;
        }
    }

    unsigned long long result{1};
    std::for_each(current.begin(), current.end(), [&result] (const auto& n) {
        const auto& [id, i]{n};
        result = std::lcm(result,i);
    });

    std::cout << result << std::endl;
}
