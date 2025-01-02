#include "utils.h"

#include <stdio.h>

/**
 * Checks whether the passed element is an value of the passed set.
 * @param value The value to check.
 * @param set The set to check against.
 * @param set_size The size of `set`.
 * @returns `1` if the value is an element of the passed set or `0` if not.
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
 * Replaces the elements of the passed with the elements of the passed replacement set.
 * @param set The set to replace the elements of.
 * @param replacement_set The set with the elements to replace with.
 * @param set_size The size of `set`.
 */
void replace_set(OrderedPair set[], OrderedPair replacement_set[], int set_size) {
  for (int index = 0; index < set_size; index++) {
    set[index][0] = replacement_set[index][0];
    set[index][1] = replacement_set[index][1];
  }
}

/**
 * Combines the elements of the passed set with the elements of the main passed set.
 * @remarks
 * This function will ignore elements that already exist in the main set.
 * @param main_set The set to combine into.
 * @param set The set to combine with the main set.
 * @param set_size The size of `main_set`.
 */
void combine_sets(OrderedPair main_set[], OrderedPair set[], int set_size) {
  OrderedPair union_set[set_size];

  for (int index = 0; index < set_size; index++) {
    union_set[index][0] = 0;
    union_set[index][1] = 0;
  }

  int union_set_index = 0;

  for (int set_index = 0; set_index < set_size; set_index++) {
    int main_set_x = main_set[set_index][0];
    int main_set_y = main_set[set_index][1];
    int set_x = set[set_index][0];
    int set_y = set[set_index][1];

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
 * Gets the amount of sets in set S that are subsets of the passed set.
 * @param set The set to use.
 * @param set_size The size of `set`.
 * @returns The number of sets that are subsets of `set`.
 */
int get_set_s_subsets_amount(OrderedPair set[], int set_size) {
  OrderedPair s[4][6] = {{{1, 1}, {1, 3}, {2, 2}, {3, 1}, {3, 3}, {0, 0}},
                         {{4, 4}, {4, 6}, {5, 5}, {6, 4}, {6, 6}, {0, 0}},
                         {{1, 5}, {2, 4}, {2, 5}, {2, 6}, {3, 5}, {0, 0}},
                         {{4, 1}, {4, 3}, {5, 1}, {5, 3}, {6, 1}, {6, 3}}};
  int intersecting_elements_amount = 0;

  for (int index = 0; index < 4; index++) {
    if (index == 3) {
      if (is_element_of_set(s[3][0], set, set_size) && is_element_of_set(s[3][1], set, set_size) &&
          is_element_of_set(s[3][2], set, set_size) && is_element_of_set(s[3][3], set, set_size) &&
          is_element_of_set(s[3][4], set, set_size) && is_element_of_set(s[3][5], set, set_size)) {
        intersecting_elements_amount++;
      }
    } else {
      if (is_element_of_set(s[index][0], set, set_size) && is_element_of_set(s[index][1], set, set_size) &&
          is_element_of_set(s[index][2], set, set_size) && is_element_of_set(s[index][3], set, set_size) &&
          is_element_of_set(s[index][4], set, set_size)) {
        intersecting_elements_amount++;
      }
    }
  }

  return intersecting_elements_amount;
}

/**
 * Gets the amount of elements the passed set contains.
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
 * Checks whether the passed set is a superset of a set in set P.
 * @param set The set to check.
 * @param set_size The size of `set`.
 * @returns `1` if `set` is a superset or `0` if not.
 */
int is_superset_of_set_p_set(OrderedPair set[], int set_size) {
  OrderedPair p[2][2] = {{{1, 1}, {2, 2}}, {{1, 2}, {2, 1}}};

  for (int index = 0; index < 2; index++) {
    if (is_element_of_set(p[index][0], set, set_size) && is_element_of_set(p[index][1], set, set_size)) return 1;
  }

  return 0;
}

/**
 * Updates the contents of set F₃ using the passed sets F₁ and F₂.
 * @param f1 The set F₁ value.
 * @param f2 The set F₂ value.
 * @param f3 The set F₃ value.
 */
void update_set_f3(FSet f1, FSet f2, FSet f3) {
  FSet new_f3 = {{1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6},
                 {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6},
                 {5, 1}, {5, 2}, {5, 3}, {5, 4}, {5, 5}, {5, 6}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {6, 6}};

  for (int index = 0; index < F_SET_SIZE; index++) {
    if (is_element_of_set(new_f3[index], f1, F_SET_SIZE) || is_element_of_set(new_f3[index], f2, F_SET_SIZE)) {
      new_f3[index][0] = 0;
      new_f3[index][1] = 0;
    }
  }

  replace_set(f3, new_f3, F_SET_SIZE);
}

/**
 * Prints this board with row and column legends to the console.
 * @param f1 The set F₁ value.
 * @param f2 The set F₂ value.
 */
void print_game_board(FSet f1, FSet f2) {
  int max_rows = 6;
  int max_columns = 6;

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
      } else if (column_number == 0) {
        printf("%d ", row_number);
      } else {
        OrderedPair coordinates = {row_number, column_number};

        if (is_element_of_set(coordinates, f1, F_SET_SIZE)) {
          printf("| A ");
        } else if (is_element_of_set(coordinates, f2, F_SET_SIZE)) {
          printf("| B ");
        } else {
          printf("|   ");
        }

        if (column_number == max_columns) printf("|\n");
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
