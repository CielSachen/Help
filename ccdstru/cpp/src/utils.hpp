#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <cstddef>
#include <cstdint>
#include <set>
#include <utility>

/** @brief A pair of X and Y values. */
typedef std::pair<std::uint_least8_t, std::uint_least8_t> OrderedPair;
/** @brief A set containing ordered pairs. */
typedef std::set<OrderedPair> Set;

/**
 * @brief Gets the amount of sets in set S that are subsets of the passed set.
 * @param set The set to check against.
 * @returns The number of sets that are subsets of `set`.
 */
std::size_t get_set_s_subsets_amount(const Set &set);

/**
 * @brief Checks whether the passed set is a superset of a set in set P.
 * @param set The set to check.
 * @returns `true` if `set` is a superset or `false` if not.
 */
bool is_superset_of_set_p_set(const Set &set);

/**
 * @brief Prints this board with row and column legends to the console.
 * @param f1 The set F₁ value.
 * @param f2 The set F₂ value.
 */
void print_game_board(const Set &f1, const Set &f2);

#endif  // UTILS_HPP_
