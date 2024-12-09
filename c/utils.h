
#include <stdbool.h>
#include <stddef.h>

#define C_SET_SIZE ((size_t)4U)
#define F_SET_SIZE ((size_t)36U)

typedef unsigned int OrderedPair[2];
typedef OrderedPair CSet[C_SET_SIZE];
typedef OrderedPair FSet[F_SET_SIZE];

bool IsElementOfSet(OrderedPair element, OrderedPair set[], size_t set_size);

void PrintGameBoard(FSet F1, FSet F2);

void ReplaceSet(OrderedPair set[], OrderedPair replacement_set[], size_t set_size);

void CreateNewSetF3(FSet F1, FSet F2, FSet F3);

void CombineSets(OrderedPair set_one[], OrderedPair set_two[], size_t set_size);

size_t GetElementsIntersectingSetSAmount(OrderedPair set[], size_t set_size);

size_t GetSetLength(OrderedPair set[], size_t set_size);

bool IsContainingAnElementOfSetP(OrderedPair set[], size_t set_size);
