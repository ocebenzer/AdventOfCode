#include <fstream>
#include <iterator>
#include <iostream>
#include <stdexcept>
#include <string>
#include <array>
#include <set>
#include <algorithm>

enum class card : uint8_t {
    J,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8,
    _9,
    T,
    Q,
    K,
    A,
};

enum strength : uint8_t {
    high_card,
    one_pair,
    two_pair,
    three_of_a_kind,
    full_house,
    four_of_a_kind,
    five_of_a_kind
};

struct hand {
    std::array<card, 5> cards;
    int bid;
    strength hand_strength;

    hand(std::string str, int bid) : bid(bid) {
        if (str.size() != 5) {
            throw std::length_error("");
        }

        std::transform(str.begin(), str.end(), cards.begin(), [] (const char c) {
            switch (c) {
                case '2': return card::_2;
                case '3': return card::_3;
                case '4': return card::_4;
                case '5': return card::_5;
                case '6': return card::_6;
                case '7': return card::_7;
                case '8': return card::_8;
                case '9': return card::_9;
                case 'T': return card::T;
                case 'J': return card::J;
                case 'Q': return card::Q;
                case 'K': return card::K;
                case 'A': return card::A;
                default:
                    throw std::invalid_argument("");
            }
        });

        long n_joker;
        std::array<int, 2> pairs{0};

        {
            auto sorted_cards = cards;
            std::sort(sorted_cards.begin(), sorted_cards.end());

            n_joker = std::count(sorted_cards.begin(), sorted_cards.end(), card::J);

            int pairs_index{0};

            auto& prev_card{sorted_cards[n_joker]};
            for (auto i{n_joker+1}; i < sorted_cards.size(); i++) {
                const auto& card{sorted_cards[i]};
                auto& diff{pairs[pairs_index]};

                if (prev_card == card) {
                    diff++;
                }
                else if (diff != 0) {
                    pairs_index++;
                }
                prev_card = card;
            }

            std::sort(pairs.begin(), pairs.end());
        }

        switch (pairs[1] + n_joker) {
            case 5:
            case 4:
                hand_strength = five_of_a_kind;
                break;
            case 3:
                hand_strength = four_of_a_kind;
                break;
            case 2: 
                if (pairs[0] == 1) hand_strength = full_house;
                else hand_strength = three_of_a_kind;
                break;
            case 1:
                if (pairs[0] == 1) hand_strength = two_pair;
                else hand_strength = one_pair;
                break;
            case 0:
            default:
                hand_strength = high_card;
                break;
        }
    }

    bool operator< (const hand& h2) const {
        if (this->hand_strength == h2.hand_strength) {
            return this->cards < h2.cards;
        }
        return this->hand_strength < h2.hand_strength;
    };
};

int main() {
    std::set<hand> hands;
    {
        std::ifstream file{"../day7.txt"};
        if (!file.is_open()) {
            std::cout << "file not open" << std::endl;
            exit(1);
        }

        std::string line;
        {
            while(!file.eof()) {
                std::string hand;
                int bid;
                file >> hand >> bid;
                if (hand.empty()) break;
                hands.insert({hand, bid});
            }
        }
    }

    long total{0};
    int points{1};

    for (const auto& hand : hands) {
        total += hand.bid * points++;
    }

    std::cout << total << std::endl;
}
