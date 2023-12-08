#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>

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

    int i{0};
    std::string current{"AAA"};
    while (current != "ZZZ") {
        const char c{rule[i % rule.size()]};
        const auto& node{nodes[current]};
        current = node.get(c);
        i++;
    }

    std::cout << i << std::endl;
}
