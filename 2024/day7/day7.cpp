#include <deque>
#include <numeric>
#include <unordered_map>

#include "utils/utils.hpp"

enum operation { add, mul, concat };

using calibration_t = std::pair<int64_t, std::vector<int64_t>>;


bool calibration_possible(const calibration_t& calibration) {
    std::deque<std::pair<calibration_t, operation>> partial_calibrations;
    partial_calibrations.emplace_back(calibration, add);
    partial_calibrations.emplace_back(calibration, mul);
    partial_calibrations.emplace_back(calibration, concat);

    while (!partial_calibrations.empty()) {
        const auto& [given, operation] = partial_calibrations.front();
        auto [result, inputs] = given;

        partial_calibrations.pop_front();

        const auto& inputs0 = *inputs.begin();
        auto& inputs1 = *(inputs.begin()+1);

        if (operation == add) {
            inputs1 += inputs0;
        }
        else if (operation == mul) {
            inputs1 *= inputs0;
        }
        else if (operation == concat) {
            std::string value = std::to_string(inputs0);
            value += std::to_string(inputs1);
            inputs1 = std::atoll(value.c_str());
        }

        if (inputs1 > result) continue;
        if (inputs.size() <= 2) {
            if (inputs1 == result) {
                return true;
            }
            continue;
        }

        const auto partial_given = std::make_pair( result, std::vector(inputs.begin()+1, inputs.end()) );
        partial_calibrations.emplace_back(partial_given, add);
        partial_calibrations.emplace_back(partial_given, mul);
        partial_calibrations.emplace_back(partial_given, concat);
    }

    return false;
}

int main() {
    const auto lines = ocb::read_lines("day7/input1.txt");

    std::vector<calibration_t> calibrations;
    for (const auto& line : lines) {
        std::stringstream ss(line);
        int64_t result, input;
        char c;
        ss >> result >> c;

        std::vector<int64_t> inputs;
        while (ss >> input) {
            inputs.emplace_back(input);
        }

        calibrations.emplace_back(result, inputs);
    }

    std::vector<int64_t> calibration_results;
    for (const auto& calibration : calibrations) {
        if (calibration_possible(calibration)) {
            calibration_results.push_back(calibration.first);
        }
    }

    const auto sum = std::accumulate(calibration_results.begin(), calibration_results.end(), static_cast<int64_t>(0));
    std::cout << sum << std::endl;
}
