#include "utils.hpp"

#include <algorithm>
#include <array>
#include <iostream>

/**
 * @brief Gets the amount of sets in set S that are subsets of the passed set.
 * @param set The set to check against.
 * @returns The number of sets that are subsets of `set`.
 */
std::size_t get_set_s_subsets_amount(const Set &set) {
    const std::array<Set, 4> s = {{{{1, 1}, {1, 3}, {2, 2}, {3, 1}, {3, 3}},
                                   {{4, 4}, {4, 6}, {5, 5}, {6, 4}, {6, 6}},
                                   {{1, 5}, {2, 4}, {2, 5}, {2, 6}, {3, 5}},
                                   {{4, 1}, {4, 3}, {5, 1}, {5, 3}, {6, 1}, {6, 3}}}};
    std::size_t subsets_amount = 0;

    for (const auto &s_set : s) {
        if (std::all_of(s_set.cbegin(), s_set.cend(),
                        [=](OrderedPair element) { return set.find(element) != set.end(); })) {
            subsets_amount += 1;
        }
    }

    return subsets_amount;
}

/**
 * @brief Checks whether the passed set is a superset of a set in set P.
 * @param set The set to check.
 * @returns `true` if `set` is a superset or `false` if not.
 */
bool is_superset_of_set_p_set(const Set &set) {
    const std::array<Set, 2> p = {{{{1, 1}, {2, 2}}, {{1, 2}, {2, 1}}}};

    for (const auto &p_set : p) {
        if (std::all_of(p_set.cbegin(), p_set.cend(),
                        [=](OrderedPair element) { return set.find(element) != set.end(); })) {
            return true;
        }
    }

    return false;
}

/**
 * @brief Prints this board with row and column legends to the console.
 * @param f1 The set F₁ value.
 * @param f2 The set F₂ value.
 */
void print_game_board(const Set &f1, const Set &f2) {
    const int maximum_rows = 6;
    const int maximum_columns = 6;

    for (int row_number = 0; row_number <= maximum_rows; row_number++) {
        for (int column_number = 0; column_number <= maximum_columns; column_number++) {
            if (row_number == 0) {
                std::cout << "  ";

                if (column_number > 0) {
                    std::cout << column_number;

                    if (column_number == maximum_columns) {
                        std::cout << std::endl;
                    } else {
                        std::cout << " ";
                    }
                }
            } else if (column_number == 0) {
                std::cout << row_number << " ";
            } else {
                OrderedPair coordinates = {column_number, row_number};

                if (f1.find(coordinates) != f1.end()) {
                    std::cout << "| A ";
                } else if (f2.find(coordinates) != f2.end()) {
                    std::cout << "| B ";
                } else {
                    std::cout << "|   ";
                }

                if (column_number == maximum_columns) {
                    std::cout << "|" << std::endl;
                }
            }
        }

        std::cout << "  ";

        for (int column_number = 1; column_number <= maximum_columns; column_number++) {
            std::cout << "+---";

            if (column_number == maximum_columns) {
                std::cout << "+" << std::endl;
            }
        }
    }

    std::cout << std::endl;
}
