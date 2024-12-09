#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

/**
 * Implements the `NextPlayerMove(pos ∈ F)` function.
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
void next_player_move(OrderedPair pos, int over, int next, FSet f3, int *good, FSet f1, FSet f2, CSet c1, CSet c2) {
  int a = pos[0];
  int b = pos[1];
  FSet pos_set = {{a, b}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                  {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                  {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
  int c = floor((a - 1) / 3) + 1;
  int d = floor((b - 1) / 3) + 1;
  CSet cd_set = {{c, d}, {0, 0}, {0, 0}, {0, 0}};

  if (!over && next && is_element_of_set(pos, f3, F_SET_SIZE)) {
    *good = !*good;

    combine_sets(f1, pos_set, F_SET_SIZE);
  }

  if (!over && !next && is_element_of_set(pos, f3, F_SET_SIZE)) {
    *good = !*good;

    combine_sets(f2, pos_set, F_SET_SIZE);
  }

  if (!over && *good && next && get_set_S_subsets_amount(f1, F_SET_SIZE) > get_actual_set_size(c1, C_SET_SIZE)) {
    combine_sets(c1, cd_set, C_SET_SIZE);
  }

  if (!over && *good && !next && get_set_S_subsets_amount(f2, F_SET_SIZE) > get_actual_set_size(c2, C_SET_SIZE)) {
    combine_sets(c2, cd_set, C_SET_SIZE);
  }

  if (!over && *good) *good = !*good;
}

/**
 * Implements the `GameOver(over)` function.
 * @param over The over element value.
 * @param[in,out] next The next element value.
 * @param c1 The set C₁ value.
 * @param c2 The set C₂ value.
 * @param[out] result The result element value.
 */
void game_over(int over, int *next, CSet c1, CSet c2, char **result) {
  if (over && *next && get_actual_set_size(c1, C_SET_SIZE) > 0 && is_containing_an_element_of_set_P(c1, C_SET_SIZE)) {
    *result = "A wins";
  }

  if (over && !*next && get_actual_set_size(c2, C_SET_SIZE) > 0 && is_containing_an_element_of_set_P(c2, C_SET_SIZE)) {
    *result = "B wins";
  }

  if (!over) *next = !*next;
}

int main(void) {
  FSet f1 = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
             {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
             {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
  FSet f2 = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
             {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
             {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
  FSet f3;

  update_set_f3(f1, f2, f3);

  int over = 0;
  int next = 0;
  int good = 0;
  CSet c1 = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
  CSet c2 = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
  char *result = "A and Player B are tied";

  while (!over) {
    print_game_board(f1, f2);

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

      if (!is_element_of_set(pos, f3, F_SET_SIZE)) {
        printf("Please input the location of an unoccupied tile.\n");

        continue;
      }

      break;
    }

    next_player_move(pos, over, next, f3, &good, f1, f2, c1, c2);

    update_set_f3(f1, f2, f3);

    over = get_actual_set_size(f3, F_SET_SIZE) == 0 ||
           (get_actual_set_size(c1, C_SET_SIZE) > 0 && is_containing_an_element_of_set_P(c1, C_SET_SIZE)) ||
           (get_actual_set_size(c2, C_SET_SIZE) > 0 && is_containing_an_element_of_set_P(c2, C_SET_SIZE));

    game_over(over, &next, c1, c2, &result);

    printf("\n");
  }

  print_game_board(f1, f2);

  printf("Player %s!\n", result);
}
