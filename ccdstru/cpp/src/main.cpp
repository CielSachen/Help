#include <cmath>
#include <iostream>
#include <string>

#include "utils.hpp"

/**
 * @brief Implements the `NextPlayerMove(pos ∈ F)` function.
 * @param pos The pos element value.
 * @param over The over element value.
 * @param next The next element value.
 * @param f3 The set F₃ value.
 * @param good The good element value.
 * @param f1 The set F₁ value.
 * @param f2 The set F₂ value.
 * @param c1 The set C₁ value.
 * @param c2 The set C₂ value.
 */
void next_player_move(const OrderedPair pos, const bool over, const bool next, const Set &f3,
                      bool &good, Set &f1, Set &f2, Set &c1, Set &c2) {
    const int a = pos.first;
    const int b = pos.second;
    const int c = floor((a - 1) / 3) + 1;
    const int d = floor((b - 1) / 3) + 1;

    if (!over && next && f3.find(pos) != f3.end()) {
        good = !good;

        f1.insert(pos);
    }

    if (!over && !next && f3.find(pos) != f3.end()) {
        good = !good;

        f2.insert(pos);
    }

    if (!over && good && next && get_set_s_subsets_amount(f1) > c1.size()) {
        c1.insert({c, d});
    }

    if (!over && good && !next && get_set_s_subsets_amount(f2) > c2.size()) {
        c2.insert({c, d});
    }

    if (!over && good) {
        good = !good;
    }
}

/**
 * @brief Implements the `GameOver(over)` function.
 * @param over The over element value.
 * @param next The next element value.
 * @param c1 The set C₁ value.
 * @param c2 The set C₂ value.
 * @param result The result element value.
 */
void game_over(const bool over, bool &next, const Set &c1, const Set &c2, std::string &result) {
    if (over && next && c1.size() > 0 && is_superset_of_set_p_set(c1)) result = "A wins";

    if (over && !next && c2.size() > 0 && is_superset_of_set_p_set(c2)) result = "B wins";

    if (!over) {
        next = !next;
    }
}

int main(void) {
    Set f1;
    Set f2;
    Set f3 = {{1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {2, 1}, {2, 2}, {2, 3},
              {2, 4}, {2, 5}, {2, 6}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6},
              {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {5, 1}, {5, 2}, {5, 3},
              {5, 4}, {5, 5}, {5, 6}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {6, 6}};
    bool over = false;
    bool next = false;
    bool good = false;
    Set c1;
    Set c2;
    std::string result = "A and Player B are tied";

    while (!over) {
        print_game_board(f1, f2);

        std::cout << "Player " << (next ? "A" : "B") << "'s Turn," << std::endl;

        OrderedPair pos;

        while (true) {
            std::cout << "Input the tile's location {XY | X = Column, Y = Row}: " << std::flush;

            std::uint_least8_t given_coordinates;
            std::string buffer;

            std::getline(std::cin, buffer);

            try {
                given_coordinates = std::stoi(buffer);
            } catch (...) {
                given_coordinates = 0;
            }

            if (given_coordinates < 11 || given_coordinates > 66) {
                std::cout << "Please input a location within the board." << std::endl;

                continue;
            }

            pos.first = given_coordinates / 10;
            pos.second = given_coordinates % 10;

            if (!(f3.find(pos) != f3.end())) {
                std::cout << "Please input the location of an unoccupied tile." << std::endl;

                continue;
            }

            break;
        }

        next_player_move(pos, over, next, f3, good, f1, f2, c1, c2);

        f3.erase(pos);

        over = f3.size() == 0 || (c1.size() > 0 && is_superset_of_set_p_set(c1)) ||
               (c2.size() > 0 && is_superset_of_set_p_set(c2));

        game_over(over, next, c1, c2, result);

        std::cout << std::endl;
    }

    print_game_board(f1, f2);

    std::cout << "Player " << result << "!" << std::endl;
}
