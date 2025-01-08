#ifndef UTILS_H_
#define UTILS_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/** @brief A pair of two integer values with fixed order. */
typedef uint_least8_t OrderedPair[2];

/** @brief The size of set C and all of its subsets. */
#define C_SET_SIZE 4
/** @brief The size of set F and all of its subsets. */
#define F_SET_SIZE 36

/** @brief A subset of Set C containing ordered pairs. */
typedef OrderedPair CSet[C_SET_SIZE];
/** @brief A subset of Set F containing ordered pairs. */
typedef OrderedPair FSet[F_SET_SIZE];

/**
 * @brief Checks whether the passed set contains the passed element.
 * @param element The element to check.
 * @param set The set to check against.
 * @param set_size The size of `set`.
 * @returns `true` if the passed set contains the passed element or `false` if not.
 */
bool is_element_of_set(const OrderedPair element, OrderedPair set[restrict], const size_t set_size);

/**
 * @brief Replaces the elements of the passed with the elements of the passed replacement set.
 * @param set The set to replace the elements of.
 * @param replacement_set The set with the elements to replace with.
 * @param set_size The size of `set`.
 */
void replace_set(OrderedPair set[restrict], OrderedPair replacement_set[restrict],
                 const size_t set_size);

/**
 * @brief Combines the elements of the passed set with the elements of the main passed set.
 * @note This function will ignore elements that already exist in the main set.
 * @param main_set The set to combine into.
 * @param set The set to combine with the main set.
 * @param set_size The size of `main_set`.
 */
void combine_sets(OrderedPair main_set[restrict], OrderedPair set[restrict], const size_t set_size);

/**
 * @brief Counts the number of sets in set S that are subsets of the passed set.
 * @param set The set to check against.
 * @param set_size The size of `set`.
 * @returns The number of sets that are subsets of `set`.
 */
size_t count_set_s_subsets(OrderedPair set[restrict], const size_t set_size);

/**
 * @brief Gets the number of elements the passed set contains.
 * @param set The set to get the actual size of.
 * @param set_size The size of `set`.
 * @returns The number of elements `set` contains.
 */
size_t get_actual_set_size(OrderedPair set[restrict], const size_t set_size);

/**
 * @brief Checks whether the passed set is a superset of a set in set P.
 * @param set The set to check.
 * @param set_size The size of `set`.
 * @returns `true` if `set` is a superset or `false` if not.
 */
bool is_superset_of_set_p_set(OrderedPair set[restrict], const size_t set_size);

/**
 * @brief Removes the passed element from the passed set.
 * @param set The set to remove from.
 * @param element The element to remove.
 */
void remove_element_from_set(const OrderedPair element, OrderedPair set[restrict],
                             const size_t set_size);

/**
 * @brief Prints the board with row and column legends to the console.
 * @param f1 The set F₁ value.
 * @param f2 The set F₂ value.
 */
void print_game_board(FSet f1, FSet f2);

#endif  // UTILS_H_
