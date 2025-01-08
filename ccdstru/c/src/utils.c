#include "utils.h"

#include <stdio.h>

/**
 * @brief Checks whether the passed set contains the passed element.
 * @param element The element to check.
 * @param set The set to check against.
 * @param set_size The size of `set`.
 * @returns `true` if the set contains the element or `false` if not.
 */
bool is_element_of_set(const OrderedPair element, OrderedPair set[restrict],
                       const size_t set_size) {
    for (size_t index = 0; index < set_size; index++) {
        if (set[index][0] != 0 && set[index][1] != 0 && set[index][0] == element[0] &&
            set[index][1] == element[1]) {
            return true;
        }
    }

    return false;
}

/**
 * @brief Replaces the elements of the passed with the elements of the passed replacement set.
 * @param set The set to replace the elements of.
 * @param replacement_set The set with the elements to replace with.
 * @param set_size The size of `set`.
 */
void replace_set(OrderedPair set[restrict], OrderedPair replacement_set[restrict],
                 const size_t set_size) {
    for (size_t index = 0; index < set_size; index++) {
        set[index][0] = replacement_set[index][0];
        set[index][1] = replacement_set[index][1];
    }
}

/**
 * @brief Combines the elements of the passed set with the elements of the main passed set.
 * @note This function will ignore elements that already exist in the main set.
 * @param main_set The set to combine into.
 * @param set The set to combine with the main set.
 * @param set_size The size of `main_set`.
 */
void combine_sets(OrderedPair main_set[restrict], OrderedPair set[restrict],
                  const size_t set_size) {
    OrderedPair union_set[set_size];

    for (size_t index = 0; index < set_size; index++) {
        union_set[index][0] = 0;
        union_set[index][1] = 0;
    }

    size_t union_set_index = 0;

    for (size_t set_index = 0; set_index < set_size; set_index++) {
        uint_least8_t main_set_x = main_set[set_index][0];
        uint_least8_t main_set_y = main_set[set_index][1];
        uint_least8_t set_x = set[set_index][0];
        uint_least8_t set_y = set[set_index][1];

        if (main_set_x != 0 && main_set_y != 0) {
            union_set[union_set_index][0] = main_set_x;
            union_set[union_set_index][1] = main_set_y;

            union_set_index++;
        }

        if (set_x != 0 && set_y != 0 && !is_element_of_set(set[set_index], main_set, set_size)) {
            union_set[union_set_index][0] = set_x;
            union_set[union_set_index][1] = set_y;

            union_set_index++;
        }
    }

    replace_set(main_set, union_set, set_size);
}

/**
 * @brief Counts the number of sets in set S that are subsets of the passed set.
 * @param set The set to check against.
 * @param set_size The size of `set`.
 * @returns The number of sets that are subsets of `set`.
 */
size_t count_set_s_subsets(OrderedPair set[restrict], const size_t set_size) {
    OrderedPair s[4][6] = {{{1, 1}, {1, 3}, {2, 2}, {3, 1}, {3, 3}, {0, 0}},
                           {{4, 4}, {4, 6}, {5, 5}, {6, 4}, {6, 6}, {0, 0}},
                           {{1, 5}, {2, 4}, {2, 5}, {2, 6}, {3, 5}, {0, 0}},
                           {{4, 1}, {4, 3}, {5, 1}, {5, 3}, {6, 1}, {6, 3}}};
    size_t subsets_count = 0;

    for (size_t index = 0; index < 4; index++) {
        if (index == 3) {
            if (is_element_of_set(s[3][0], set, set_size) &&
                is_element_of_set(s[3][1], set, set_size) &&
                is_element_of_set(s[3][2], set, set_size) &&
                is_element_of_set(s[3][3], set, set_size) &&
                is_element_of_set(s[3][4], set, set_size) &&
                is_element_of_set(s[3][5], set, set_size)) {
                subsets_count++;
            }
        } else if (is_element_of_set(s[index][0], set, set_size) &&
                   is_element_of_set(s[index][1], set, set_size) &&
                   is_element_of_set(s[index][2], set, set_size) &&
                   is_element_of_set(s[index][3], set, set_size) &&
                   is_element_of_set(s[index][4], set, set_size)) {
            subsets_count++;
        }
    }

    return subsets_count;
}

/**
 * @brief Gets the number of elements the passed set contains.
 * @param set The set to get the actual size of.
 * @param set_size The size of `set`.
 * @returns The number of elements `set` contains.
 */
size_t get_actual_set_size(OrderedPair set[restrict], const size_t set_size) {
    size_t actual_set_size = 0;

    for (size_t index = 0; index < set_size; index++) {
        if (set[index][0] != 0 && set[index][1] != 0) {
            actual_set_size++;
        }
    }

    return actual_set_size;
}

/**
 * @brief Checks whether the passed set is a superset of a set in set P.
 * @param set The set to check.
 * @param set_size The size of `set`.
 * @returns `true` if `set` is a superset or `false` if not.
 */
bool is_superset_of_set_p_set(OrderedPair set[restrict], const size_t set_size) {
    OrderedPair p[2][2] = {{{1, 1}, {2, 2}}, {{1, 2}, {2, 1}}};

    for (size_t index = 0; index < 2; index++) {
        if (is_element_of_set(p[index][0], set, set_size) &&
            is_element_of_set(p[index][1], set, set_size)) {
            return true;
        }
    }

    return false;
}

/**
 * @brief Removes the passed element from the passed set.
 * @param set The set to remove from.
 * @param element The element to remove.
 */
void remove_element_from_set(const OrderedPair element, OrderedPair set[restrict],
                             const size_t set_size) {
    for (size_t index = 0; index < set_size; index++) {
        if (set[index][0] == element[0] && set[index][1] == element[1]) {
            set[index][0] = 0;
            set[index][1] = 0;

            return;
        }
    }
}

/**
 * @brief Prints the board with row and column legends to the console.
 * @param f1 The set F₁ value.
 * @param f2 The set F₂ value.
 */
void print_game_board(FSet f1, FSet f2) {
    const int maximum_rows = 6;
    const int maximum_columns = 6;

    for (int row_number = 0; row_number <= maximum_rows; row_number++) {
        for (int column_number = 0; column_number <= maximum_columns; column_number++) {
            if (row_number == 0) {
                printf("  ");

                if (column_number > 0) {
                    printf("%d", column_number);

                    if (column_number == maximum_columns) {
                        printf("\n");
                    } else {
                        printf(" ");
                    }
                }
            } else if (column_number == 0) {
                printf("%d ", row_number);
            } else {
                OrderedPair coordinates = {column_number, row_number};

                if (is_element_of_set(coordinates, f1, F_SET_SIZE)) {
                    printf("| A ");
                } else if (is_element_of_set(coordinates, f2, F_SET_SIZE)) {
                    printf("| B ");
                } else {
                    printf("|   ");
                }

                if (column_number == maximum_columns) {
                    printf("|\n");
                }
            }
        }

        printf("  ");

        for (int column_number = 1; column_number <= maximum_columns; column_number++) {
            printf("+---");

            if (column_number == maximum_columns) {
                printf("+\n");
            }
        }
    }

    printf("\n");
}
