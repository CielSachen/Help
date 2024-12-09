#include "utils.h"

#include <stdio.h>

/**
 * Checks whether or not the provided element is an value of the provided set.
 * @param value The value to check.
 * @param set The set to check against.
 * @param set_size The size of the provided set.
 * @returns `1` if the value is an element of the provided set or `0` if not.
 */
int is_element_of_set(OrderedPair value, OrderedPair set[], int set_size) {
  for (int index = 0; index < set_size; index++) {
    if (set[index][0] != 0 && set[index][1] != 0 && set[index][0] == value[0] && set[index][1] == value[1]) {
      return 1;
    }
  }

  return 0;
}

/**
 * Prints this board with row and column legends to the console.
 * @param F1 The set F₁ value.
 * @param F2 The set F₂ value.
 */
void print_game_board(FSet F1, FSet F2) {
  int max_columns = 6;
  int max_rows = 6;

  for (int row_number = 0; row_number <= max_rows; row_number++) {
    for (int column_number = 0; column_number <= max_columns; column_number++) {
      if (row_number == 0) {
        printf("  ");

        if (column_number > 0) {
          printf("%d", column_number);

          if (column_number == max_columns) {
            printf("\n");
          } else {
            printf(" ");
          }
        }
      } else {
        if (column_number == 0) {
          printf("%d ", row_number);
        } else {
          OrderedPair coordinates = {row_number, column_number};

          if (is_element_of_set(coordinates, F1, F_SET_SIZE)) {
            printf("| A ");
          } else if (is_element_of_set(coordinates, F2, F_SET_SIZE)) {
            printf("| B ");
          } else {
            printf("|   ");
          }

          if (column_number == max_columns) printf("|\n");
        }
      }
    }

    printf("  ");

    for (int column_number = 1; column_number <= max_columns; column_number++) {
      printf("+---");

      if (column_number == max_columns) printf("+\n");
    }
  }

  printf("\n");
}

/**
 * Replaces the elements of the provided with the elements of the provided replacement set.
 * @param set The set to replace the elements of.
 * @param replacement_set The set with the elements to replace with.
 * @param set_size The size of the provided set.
 */
void replace_set(OrderedPair original_set[], OrderedPair replacement_set[], int set_size) {
  for (int index = 0; index < set_size; index++) {
    original_set[index][0] = replacement_set[index][0];
    original_set[index][1] = replacement_set[index][1];
  }
}

/**
 * Updates the contents of set F₃ using the provided sets F₁ and F₂.
 * @param F1 The set F₁ value.
 * @param F2 The set F₂ value.
 * @param F2 The set F₃ value.
 */
void update_set_F3(FSet F1, FSet F2, FSet F3) {
  FSet new_F3 = {{1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6},
                 {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6},
                 {5, 1}, {5, 2}, {5, 3}, {5, 4}, {5, 5}, {5, 6}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {6, 6}};

  for (int new_F_set_index = 0; new_F_set_index < F_SET_SIZE; new_F_set_index++) {
    int is_existing_element = 0;

    for (int F_set_index = 0; F_set_index < F_SET_SIZE; F_set_index++) {
      if ((new_F3[new_F_set_index][0] == F1[F_set_index][0] && new_F3[new_F_set_index][1] == F1[F_set_index][1]) ||
          (new_F3[new_F_set_index][0] == F2[F_set_index][0] && new_F3[new_F_set_index][1] == F2[F_set_index][1])) {
        is_existing_element = 1;

        break;
      }
    }

    if (is_existing_element) {
      new_F3[new_F_set_index][0] = 0;
      new_F3[new_F_set_index][1] = 0;
    }
  }

  replace_set(F3, new_F3, F_SET_SIZE);
}

/**
 * Combines the elements of the provided set with the elements of the main provided set.
 * @remarks
 * This function will ignore elements that already exist in the main set.
 * @param main_set The set to combine into.
 * @param set The set to combine with the main set.
 * @param set_size The size of `main_set`.
 */
void combine_sets(OrderedPair set_one[], OrderedPair set_two[], int set_size) {
  OrderedPair union_set[set_size];

  for (int index = 0; index < set_size; index++) {
    union_set[index][0] = 0;
    union_set[index][1] = 0;
  }

  int union_set_index = 0;

  for (int set_index = 0; set_index < set_size; set_index++) {
    int set_one_x = set_one[set_index][0];
    int set_one_y = set_one[set_index][1];
    int set_two_x = set_two[set_index][0];
    int set_two_y = set_two[set_index][1];

    if (set_one_x != 0 && set_one_y != 0) {
      union_set[union_set_index][0] = set_one_x;
      union_set[union_set_index][1] = set_one_y;

      union_set_index++;
    }

    if (set_two_x != 0 && set_two_y != 0 && !is_element_of_set(set_two[set_index], set_one, set_size)) {
      union_set[union_set_index][0] = set_two_x;
      union_set[union_set_index][1] = set_two_y;

      union_set_index++;
    }
  }

  replace_set(set_one, union_set, set_size);
}

/**
 * Gets the amount of elements the provided set contains that intersects with set S.
 * @param set The set to use.
 * @param set_size The size of `set`.
 * @returns The number of elements of `set` that intersect.
 */
int get_elements_intersecting_set_S_amount(OrderedPair set[], int set_size) {
  OrderedPair S[4][6] = {{{1, 1}, {1, 3}, {2, 2}, {3, 1}, {3, 3}, {0, 0}},
                         {{4, 4}, {4, 6}, {5, 5}, {6, 4}, {6, 6}, {0, 0}},
                         {{1, 5}, {2, 4}, {2, 5}, {2, 6}, {3, 5}, {0, 0}},
                         {{4, 1}, {4, 3}, {5, 1}, {5, 3}, {6, 1}, {6, 3}}};
  int intersecting_elements_amount = 0;

  for (int index = 0; index < 4; index++) {
    if (index == 3) {
      if (is_element_of_set(S[3][0], set, set_size) && is_element_of_set(S[3][1], set, set_size) &&
          is_element_of_set(S[3][2], set, set_size) && is_element_of_set(S[3][3], set, set_size) &&
          is_element_of_set(S[3][4], set, set_size) && is_element_of_set(S[3][5], set, set_size)) {
        intersecting_elements_amount++;
      }
    } else {
      if (is_element_of_set(S[index][0], set, set_size) && is_element_of_set(S[index][1], set, set_size) &&
          is_element_of_set(S[index][2], set, set_size) && is_element_of_set(S[index][3], set, set_size) &&
          is_element_of_set(S[index][4], set, set_size)) {
        intersecting_elements_amount++;
      }
    }
  }

  return intersecting_elements_amount;
}

/**
 * Gets the amount of elements the provided set contains.
 * @param set The set to get the actual size of.
 * @param set_size The size of `set`.
 * @returns The number of elements `set` contains.
 */
int get_actual_set_size(OrderedPair set[], int set_size) {
  int actual_set_size = 0;

  for (int index = 0; index < set_size; index++) {
    if (set[index][0] != 0 && set[index][1] != 0) actual_set_size++;
  }

  return actual_set_size;
}

/**
 * Checks whether or not the provided set contains an element of set P.
 * @param set The set to check.
 * @param set_size The size of `set`.
 * @returns `1` if `set` contains an element of set P or `0` if not.
 */
int is_containing_an_element_of_set_P(OrderedPair set[], int set_size) {
  OrderedPair P[2][2] = {{{1, 1}, {2, 2}}, {{1, 2}, {2, 1}}};

  for (int index = 0; index < 2; index++) {
    if (is_element_of_set(P[index][0], set, set_size) && is_element_of_set(P[index][1], set, set_size)) return 1;
  }

  return 0;
}
