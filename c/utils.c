#include "utils.h"

#include <stdio.h>

bool IsElementOfSet(OrderedPair element, OrderedPair set[], size_t set_size) {
  for (int index = 0; index < set_size; index++) {
    if (set[index][0] != 0 && set[index][1] != 0 && set[index][0] == element[0] && set[index][1] == element[1]) {
      return true;
    }
  }

  return false;
}

void PrintGameBoard(FSet F1, FSet F2) {
  unsigned int max_columns = 6;
  unsigned int max_rows = 6;

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

          if (IsElementOfSet(coordinates, F1, F_SET_SIZE)) {
            printf("| A ");
          } else if (IsElementOfSet(coordinates, F2, F_SET_SIZE)) {
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

void ReplaceSet(OrderedPair original_set[], OrderedPair replacement_set[], size_t set_size) {
  for (int index = 0; index < set_size; index++) {
    original_set[index][0] = replacement_set[index][0];
    original_set[index][1] = replacement_set[index][1];
  }
}

void CreateNewSetF3(FSet F1, FSet F2, FSet F3) {
  FSet new_F3 = {{1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6},
                 {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6},
                 {5, 1}, {5, 2}, {5, 3}, {5, 4}, {5, 5}, {5, 6}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {6, 6}};

  for (int new_F_set_index = 0; new_F_set_index < F_SET_SIZE; new_F_set_index++) {
    bool is_existing_element = false;

    for (int F_set_index = 0; F_set_index < F_SET_SIZE; F_set_index++) {
      if ((new_F3[new_F_set_index][0] == F1[F_set_index][0] && new_F3[new_F_set_index][1] == F1[F_set_index][1]) ||
          (new_F3[new_F_set_index][0] == F2[F_set_index][0] && new_F3[new_F_set_index][1] == F2[F_set_index][1])) {
        is_existing_element = true;

        break;
      }
    }

    if (is_existing_element) {
      new_F3[new_F_set_index][0] = 0;
      new_F3[new_F_set_index][1] = 0;
    }
  }

  ReplaceSet(F3, new_F3, F_SET_SIZE);
}

void CombineSets(OrderedPair set_one[], OrderedPair set_two[], size_t set_size) {
  OrderedPair union_set[set_size];

  for (int index = 0; index < set_size; index++) {
    union_set[index][0] = 0;
    union_set[index][1] = 0;
  }

  int union_set_index = 0;

  for (int set_index = 0; set_index < set_size; set_index++) {
    unsigned int set_one_x = set_one[set_index][0];
    unsigned int set_one_y = set_one[set_index][1];
    unsigned int set_two_x = set_two[set_index][0];
    unsigned int set_two_y = set_two[set_index][1];

    if (set_one_x != 0 && set_one_y != 0) {
      union_set[union_set_index][0] = set_one_x;
      union_set[union_set_index][1] = set_one_y;

      union_set_index++;
    }

    if (set_two_x != 0 && set_two_y != 0 && !IsElementOfSet(set_two[set_index], set_one, set_size)) {
      union_set[union_set_index][0] = set_two_x;
      union_set[union_set_index][1] = set_two_y;

      union_set_index++;
    }
  }

  ReplaceSet(set_one, union_set, set_size);
}

size_t GetElementsIntersectingSetSAmount(OrderedPair set[], size_t set_size) {
  OrderedPair S[4][6] = {{{1, 1}, {1, 3}, {2, 2}, {3, 1}, {3, 3}, {0, 0}},
                         {{4, 4}, {4, 6}, {5, 5}, {6, 4}, {6, 6}, {0, 0}},
                         {{1, 5}, {2, 4}, {2, 5}, {2, 6}, {3, 5}, {0, 0}},
                         {{4, 1}, {4, 3}, {5, 1}, {5, 3}, {6, 1}, {6, 3}}};
  size_t intersecting_elements_amount = 0;

  for (int index = 0; index < 4; index++) {
    if (index == 3) {
      if (IsElementOfSet(S[3][0], set, set_size) && IsElementOfSet(S[3][1], set, set_size) &&
          IsElementOfSet(S[3][2], set, set_size) && IsElementOfSet(S[3][3], set, set_size) &&
          IsElementOfSet(S[3][4], set, set_size) && IsElementOfSet(S[3][5], set, set_size)) {
        intersecting_elements_amount++;
      }
    } else {
      if (IsElementOfSet(S[index][0], set, set_size) && IsElementOfSet(S[index][1], set, set_size) &&
          IsElementOfSet(S[index][2], set, set_size) && IsElementOfSet(S[index][3], set, set_size) &&
          IsElementOfSet(S[index][4], set, set_size)) {
        intersecting_elements_amount++;
      }
    }
  }

  return intersecting_elements_amount;
}

size_t GetSetLength(OrderedPair set[], size_t set_size) {
  size_t set_length = 0;

  for (int index = 0; index < set_size; index++) {
    if (set[index][0] != 0 && set[index][1] != 0) set_length++;
  }

  return set_length;
}

bool IsContainingAnElementOfSetP(OrderedPair set[], size_t set_size) {
  OrderedPair P[2][2] = {{{1, 1}, {2, 2}}, {{1, 2}, {2, 1}}};

  for (int index = 0; index < 2; index++) {
    if (IsElementOfSet(P[index][0], set, set_size) && IsElementOfSet(P[index][1], set, set_size)) return true;
  }

  return false;
}
