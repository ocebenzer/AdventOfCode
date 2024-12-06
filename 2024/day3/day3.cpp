#include <regex>

#include "utils.h"

int main() {
    const auto lines = ocb::read_lines("day3/input1.txt");

    const std::regex mul_regex(R"(mul\(\d{1,3},\d{1,3}\))");
    std::smatch results;

    std::vector<std::string> valid_commands;
    for (const auto& line : lines) {
        for (auto line_iter = line.begin();
            std::regex_search(line_iter, line.end(), results, mul_regex);
            line_iter = results[0].second) {
            valid_commands.push_back(results[0]);
        }
    }

    int sum = 0;
    for (auto& command : valid_commands) {
        const auto formatted_command = regex_replace(command, std::regex("\\D"), " ");
        std::stringstream ss(formatted_command);
        int n1=0, n2=0;
        ss >> n1 >> n2;
        sum += n1 * n2;
    }

    std::cout << sum << std::endl;
}
