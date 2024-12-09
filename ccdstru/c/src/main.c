#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

/**
 * Implements the `NextPlayerMmove(pos ∈ F)` function.
 * @param pos The pos element value.
 * @param over The over element value.
 * @param next The next element value.
 * @param F2 The set F₃ value.
 * @param[in,out] good The good element value.
 * @param F1 The set F₁ value.
 * @param F2 The set F₂ value.
 * @param C1 The set C₁ value.
 * @param C2 The set C₂ value.
 */
void next_player_move(OrderedPair pos, int over, int next, FSet F3, int *good, FSet F1, FSet F2, CSet C1, CSet C2) {
  int a = pos[0];
  int b = pos[1];
  FSet pos_set = {{a, b}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                  {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                  {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
  int c = floor((a - 1) / 3) + 1;
  int d = floor((b - 1) / 3) + 1;
  CSet cd_set = {{c, d}, {0, 0}, {0, 0}, {0, 0}};

  if (!over && next && is_element_of_set(pos, F3, F_SET_SIZE)) {
    *good = !*good;

    combine_sets(F1, pos_set, F_SET_SIZE);
  } else if (!over && !next && is_element_of_set(pos, F3, F_SET_SIZE)) {
    *good = !*good;

    combine_sets(F2, pos_set, F_SET_SIZE);
  }

  if (!over && *good && next &&
      get_elements_intersecting_set_S_amount(F1, F_SET_SIZE) > get_actual_set_size(C1, C_SET_SIZE)) {
    combine_sets(C1, cd_set, C_SET_SIZE);
  } else if (!over && *good && !next &&
             get_elements_intersecting_set_S_amount(F2, F_SET_SIZE) > get_actual_set_size(C2, C_SET_SIZE)) {
    combine_sets(C2, cd_set, C_SET_SIZE);
  }

  if (!over && *good) *good = !*good;
}

/**
 * Implements the `GameOver(over)` function.
 * @param over The over element value.
 * @param[in,out] next The next element value.
 * @param C1 The set C₁ value.
 * @param C2 The set C₂ value.
 * @param[out] result The result element value.
 */
void game_over(int over, int *next, CSet C1, CSet C2, char **result) {
  if (over && *next && get_actual_set_size(C1, C_SET_SIZE) > 0 && is_containing_an_element_of_set_P(C1, C_SET_SIZE)) {
    *result = "A wins";
  } else if (over && !*next && get_actual_set_size(C2, C_SET_SIZE) > 0 &&
             is_containing_an_element_of_set_P(C2, C_SET_SIZE)) {
    *result = "B wins";
  }

  if (!over) *next = !*next;
}

int main(void) {
  FSet F1 = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
             {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
             {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
  FSet F2 = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
             {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
             {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
  FSet F3;

  update_set_F3(F1, F2, F3);

  int over = 0;
  int next = 0;
  int good = 0;
  CSet C1 = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
  CSet C2 = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
  char *result = "A and Player B are tied";

  while (!over) {
    print_game_board(F1, F2);

    if (next) {
      printf("Player A's Turn,\n");
    } else {
      printf("Player B's Turn,\n");
    }

    int given_coordinates;
    OrderedPair pos;

    while (1) {
      printf("Input the tile's location {XY | X = Column, Y = Row}: ");
      scanf(" %d", &given_coordinates);

      while (getchar() != '\n');

      if (given_coordinates < 11 || given_coordinates > 66) {
        printf("Please input a location within the board.\n");

        continue;
      }

      pos[0] = given_coordinates / 10;
      pos[1] = given_coordinates % 10;

      if (!is_element_of_set(pos, F3, F_SET_SIZE)) {
        printf("Please input the location of an unoccupied tile.\n");

        continue;
      }

      break;
    };

    next_player_move(pos, over, next, F3, &good, F1, F2, C1, C2);

    update_set_F3(F1, F2, F3);

    over = get_actual_set_size(F3, F_SET_SIZE) == 0 ||
           (get_actual_set_size(C1, C_SET_SIZE) > 0 && is_containing_an_element_of_set_P(C1, C_SET_SIZE)) ||
           (get_actual_set_size(C2, C_SET_SIZE) > 0 && is_containing_an_element_of_set_P(C2, C_SET_SIZE));

    game_over(over, &next, C1, C2, &result);

    printf("\n");
  }

  print_game_board(F1, F2);

  printf("Player %s!\n", result);
}
