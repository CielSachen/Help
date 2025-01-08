#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

/**
 * @brief Implements the `NextPlayerMove(pos ∈ F)` function.
 * @param pos The pos element value.
 * @param over The over element value.
 * @param next The next element value.
 * @param f3 The set F₃ value.
 * @param[in,out] good The good element value.
 * @param f1 The set F₁ value.
 * @param f2 The set F₂ value.
 * @param c1 The set C₁ value.
 * @param c2 The set C₂ value.
 */
void next_player_move(const OrderedPair pos, const bool over, const bool next, FSet f3,
                      bool *const good, FSet f1, FSet f2, CSet c1, CSet c2) {
    const uint_least8_t a = pos[0];
    const uint_least8_t b = pos[1];
    FSet pos_set = {{a, b}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                    {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                    {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                    {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
    const uint_least8_t c = floor((a - 1) / 3) + 1;
    const uint_least8_t d = floor((b - 1) / 3) + 1;
    CSet cd_set = {{c, d}, {0, 0}, {0, 0}, {0, 0}};

    if (!over && next && is_element_of_set(pos, f3, F_SET_SIZE)) {
        *good = !*good;

        combine_sets(f1, pos_set, F_SET_SIZE);
    }

    if (!over && !next && is_element_of_set(pos, f3, F_SET_SIZE)) {
        *good = !*good;

        combine_sets(f2, pos_set, F_SET_SIZE);
    }

    if (!over && *good && next &&
        count_set_s_subsets(f1, F_SET_SIZE) > get_actual_set_size(c1, C_SET_SIZE)) {
        combine_sets(c1, cd_set, C_SET_SIZE);
    }

    if (!over && *good && !next &&
        count_set_s_subsets(f2, F_SET_SIZE) > get_actual_set_size(c2, C_SET_SIZE)) {
        combine_sets(c2, cd_set, C_SET_SIZE);
    }

    if (!over && *good) {
        *good = !*good;
    }
}

/**
 * @brief Implements the `GameOver(over)` function.
 * @param over The over element value.
 * @param[in,out] next The next element value.
 * @param c1 The set C₁ value.
 * @param c2 The set C₂ value.
 * @param[out] result The result element value.
 */
void game_over(const bool over, bool *const next, CSet c1, CSet c2, char **const result) {
    if (over && *next && get_actual_set_size(c1, C_SET_SIZE) > 0 &&
        is_superset_of_set_p_set(c1, C_SET_SIZE)) {
        *result = "A wins";
    }

    if (over && !*next && get_actual_set_size(c2, C_SET_SIZE) > 0 &&
        is_superset_of_set_p_set(c2, C_SET_SIZE)) {
        *result = "B wins";
    }

    if (!over) {
        *next = !*next;
    }
}

int main(void) {
    FSet f1 = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
               {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
               {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
               {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
    FSet f2 = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
               {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
               {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
               {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
    FSet f3 = {{1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {2, 1}, {2, 2}, {2, 3},
               {2, 4}, {2, 5}, {2, 6}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6},
               {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {5, 1}, {5, 2}, {5, 3},
               {5, 4}, {5, 5}, {5, 6}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {6, 6}};
    bool over = false;
    bool next = false;
    bool good = false;
    CSet c1 = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
    CSet c2 = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
    char *result = "A and Player B are tied";

    while (!over) {
        print_game_board(f1, f2);

        printf("Player %c's Turn,\n", next ? 'A' : 'B');

        OrderedPair pos;

        while (true) {
            printf("Input the tile's location {XY | X = Column, Y = Row}: ");

            fflush(stdout);

            uint_least8_t given_coordinates;
            char buffer[256];

            if (!fgets(buffer, sizeof buffer, stdin)) {
                if (!strchr(buffer, '\n')) {
                    int character;

                    while ((character = getchar()) != '\n' && character != EOF) {
                    }
                }

                given_coordinates = 0;
            } else {
                given_coordinates = strtol(buffer, NULL, 10);
            }

            if (given_coordinates < 11 || given_coordinates > 66) {
                printf("Please input a location within the board.\n");

                continue;
            }

            pos[0] = given_coordinates / 10;
            pos[1] = given_coordinates % 10;

            if (!is_element_of_set(pos, f3, F_SET_SIZE)) {
                printf("Please input the location of an unoccupied tile.\n");

                continue;
            }

            break;
        }

        next_player_move(pos, over, next, f3, &good, f1, f2, c1, c2);

        remove_element_from_set(pos, f3, F_SET_SIZE);

        over =
            get_actual_set_size(f3, F_SET_SIZE) == 0 ||
            (get_actual_set_size(c1, C_SET_SIZE) > 0 && is_superset_of_set_p_set(c1, C_SET_SIZE)) ||
            (get_actual_set_size(c2, C_SET_SIZE) > 0 && is_superset_of_set_p_set(c2, C_SET_SIZE));

        game_over(over, &next, c1, c2, &result);

        printf("\n");
    }

    print_game_board(f1, f2);

    printf("Player %s!\n", result);
}
