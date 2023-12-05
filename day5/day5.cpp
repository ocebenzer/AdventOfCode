#include <cstdint>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <tuple>
#include <algorithm>
#include <span>
#include <numeric>

struct category {
    std::string_view source;
    std::string_view destination;
    std::vector<std::tuple<long, long, long>> map;

    category(std::string_view map_header, std::span<std::string> map_data) {
        source = map_header.substr(0, map_header.find('-'));
        destination = map_header.substr(map_header.find_last_of('-') + 1);

        map.resize(map_data.size());

        std::transform(map_data.begin(), map_data.end(), map.begin(),
        [] (const std::string& data) {
            std::istringstream ss{data};
            long n1, n2, n3;
            ss >> n1 >> n2 >> n3;
            return std::make_tuple(n1, n2, n3);
        });
    }

    long value(const long key) const {
        for (const auto& [destination, source, range] : map) {
            if (key >= source && key < source + range) {
                return destination + key - source;
            }
        }

        return key;
    }
};

int main() {
    std::ifstream file{"../day5.txt"};
    if (!file.is_open()) {
        std::cout << "file not open" << std::endl;
        exit(1);
    }
    
    std::vector<long> seeds;
    {
        std::string seeds_line;
        std::getline(file, seeds_line);

        std::stringstream ss{seeds_line};
        std::string token;
        ss >> token;

        while(!ss.eof()) {
            long seed;
            ss >> seed;
            seeds.push_back(seed);
        }
    }

    std::vector<std::string> lines;
    {
        std::string line;

        while (std::getline(file, line)) {
            lines.push_back(line);
        }
    }

    file.close();

    std::vector<category> almanac;
    {
        auto map_begin{lines.begin()};
        map_begin++;
        while (map_begin < lines.end()) {
            std::string_view map_header{*map_begin};
            map_header = map_header.substr(0, map_header.find(' '));

            map_begin++;
            auto map_end{map_begin + 1};
            while (map_end < lines.end() && *map_end != "") {
                map_end++;
            }

            almanac.push_back({map_header, {map_begin, map_end}});
            map_begin = map_end + 1;
        }
    }

    for (const auto& category : almanac) {
        std::transform(seeds.begin(), seeds.end(), seeds.begin(),
        [&category] (long seed) { return category.value(seed); });
    }

    std::cout << std::reduce(seeds.begin(), seeds.end(), INT64_MAX, [] (long a, long b) { return std::min(a, b); }) << std::endl;
}
