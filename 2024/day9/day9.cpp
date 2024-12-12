#include <ranges>
#include <format>

#include "utils/utils.hpp"

struct Space {
    int size;
    int id;
    bool moved;
};

int main() {
    const auto lines = ocb::read_lines("day9/input1.txt");

    std::map<int, Space> blocks;

    int block_index = 0;
    for (const auto& [index, c] : lines[0] | std::ranges::views::enumerate) {
        const auto block_size = c - '0';
        if (block_size == 0) continue;
        const int block_id = index % 2 == 0 ? index/2 : -1;
        blocks.emplace(block_index, Space{block_size, block_id, false});
        block_index += block_size;
    }

    for (int i = block_index; i >= 0; --i) {
        if (!blocks.contains(i)) continue;
        auto& move_block = blocks[i];
        if (move_block.id < 0) continue;
        if (move_block.moved) continue;
        for (int j = 0; j < i; ++j) {
            if (!blocks.contains(j)) continue;
            auto& empty_block = blocks[j];
            if (empty_block.id >= 0) continue;
            if (empty_block.size < move_block.size) continue;

            empty_block.id = move_block.id;
            const auto remaining_size = empty_block.size - move_block.size;
            empty_block.size = move_block.size;
            empty_block.moved = true;

            if (remaining_size) {
                Space shrinked_empty_block{remaining_size, -1, false};
                blocks.emplace(j + move_block.size, shrinked_empty_block);
            }

            move_block.id = -1;
            break;
        }

        const auto block_keys_view = std::ranges::views::keys(blocks);
        std::vector<int> block_keys{block_keys_view.begin(), block_keys_view.end()};
        for (auto itr = block_keys.begin()+1; itr != block_keys.end(); ++itr) {
            auto& curr = blocks[*itr];
            auto& prev = blocks[*(itr-1)];

            if (curr.id == -1 && prev.id == -1) {
                prev.size += curr.size;
                blocks.erase(*itr);
                *itr = *(itr-1);
            }
        }
    }

    auto sum = 0ull;
    for (const auto& [index, block] : blocks) {
        if (block.id == -1) continue;
        for (int i = index; i < index + block.size; ++i) {
            sum += i * block.id;
        }
    }

    std::cout << std::format("Result is: {}", sum) << std::endl;
}
