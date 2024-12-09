#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void NextPlayerMove(OrderedPair pos, bool over, bool next, FSet F3, bool *good, FSet F1, FSet F2, CSet C1, CSet C2) {
  unsigned int a = pos[0];
  unsigned int b = pos[1];
  FSet pos_set = {{a, b}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                  {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                  {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
  unsigned int c = floor((a - 1) / 3) + 1;
  unsigned int d = floor((b - 1) / 3) + 1;
  CSet cd_set = {{c, d}, {0, 0}, {0, 0}, {0, 0}};

  if (!over && next && IsElementOfSet(pos, F3, F_SET_SIZE)) {
    *good = !*good;

    CombineSets(F1, pos_set, F_SET_SIZE);
  } else if (!over && !next && IsElementOfSet(pos, F3, F_SET_SIZE)) {
    *good = !*good;

    CombineSets(F2, pos_set, F_SET_SIZE);
  }

  if (!over && *good && next && GetElementsIntersectingSetSAmount(F1, F_SET_SIZE) > GetSetLength(C1, C_SET_SIZE)) {
    CombineSets(C1, cd_set, C_SET_SIZE);
  } else if (!over && *good && !next &&
             GetElementsIntersectingSetSAmount(F2, F_SET_SIZE) > GetSetLength(C2, C_SET_SIZE)) {
    CombineSets(C2, cd_set, C_SET_SIZE);
  }

  if (!over && *good) *good = !*good;
}

void GameOver(bool over, bool *next, CSet C1, CSet C2, char **result) {
  if (over && *next && GetSetLength(C1, C_SET_SIZE) > 0 && IsContainingAnElementOfSetP(C1, C_SET_SIZE)) {
    *result = "A wins";
  } else if (over && !*next && GetSetLength(C2, C_SET_SIZE) > 0 && IsContainingAnElementOfSetP(C2, C_SET_SIZE)) {
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

  CreateNewSetF3(F1, F2, F3);

  bool over = false;
  // Switched the initial value to make player A first.
  bool next = true;
  bool good = false;
  CSet C1 = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
  CSet C2 = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
  char *result = "A and Player B are tied";

  while (!over) {
    PrintGameBoard(F1, F2);

    if (next) {
      printf("Player A's Turn,\n");
    } else {
      printf("Player B's Turn,\n");
    }

    int given_coordinates;
    OrderedPair pos;

    while (true) {
      printf("Input the tile's location {XY | X = Column, Y = Row}: ");
      scanf(" %d", &given_coordinates);

      while (getchar() != '\n');

      if (given_coordinates < 11 || given_coordinates > 66) {
        printf("Please input a location within the board.\n");

        continue;
      }

      pos[0] = given_coordinates / 10;
      pos[1] = given_coordinates % 10;

      if (!IsElementOfSet(pos, F3, F_SET_SIZE)) {
        printf("Please input the location of an unoccupied tile.\n");

        continue;
      }

      break;
    };

    NextPlayerMove(pos, over, next, F3, &good, F1, F2, C1, C2);

    CreateNewSetF3(F1, F2, F3);

    over = GetSetLength(F3, F_SET_SIZE) == 0 ||
           (GetSetLength(C1, C_SET_SIZE) > 0 && IsContainingAnElementOfSetP(C1, C_SET_SIZE)) ||
           (GetSetLength(C2, C_SET_SIZE) > 0 && IsContainingAnElementOfSetP(C2, C_SET_SIZE));

    GameOver(over, &next, C1, C2, &result);

    printf("\n");
  }

  PrintGameBoard(F1, F2);

  printf("Player %s!\n", result);
}
