/** The size of set C and all of its subsets. */
#define C_SET_SIZE 4
/** The size of set F and all of its subsets. */
#define F_SET_SIZE 36

/** A pair of X and Y values. */
typedef int OrderedPair[2];
/** A subset of Set C containing ordered pairs. */
typedef OrderedPair CSet[C_SET_SIZE];
/** A subset of Set F containing ordered pairs. */
typedef OrderedPair FSet[F_SET_SIZE];

/**
 * Checks whether the passed element is an value of the passed set.
 * @param value The value to check.
 * @param set The set to check against.
 * @param set_size The size of `set`.
 * @returns `1` if the value is an element of the passed set or `0` if not.
 */
int is_element_of_set(OrderedPair value, OrderedPair set[], int set_size);

/**
 * Replaces the elements of the passed with the elements of the passed replacement set.
 * @param set The set to replace the elements of.
 * @param replacement_set The set with the elements to replace with.
 * @param set_size The size of `set`.
 */
void replace_set(OrderedPair set[], OrderedPair replacement_set[], int set_size);

/**
 * Combines the elements of the passed set with the elements of the main passed set.
 * @remarks
 * This function will ignore elements that already exist in the main set.
 * @param main_set The set to combine into.
 * @param set The set to combine with the main set.
 * @param set_size The size of `main_set`.
 */
void combine_sets(OrderedPair main_set[], OrderedPair set[], int set_size);

/**
 * Gets the amount of sets in set S that are subsets of the passed set.
 * @param set The set to use.
 * @param set_size The size of `set`.
 * @returns The number of sets that are subsets of `set`.
 */
int get_set_s_subsets_amount(OrderedPair set[], int set_size);

/**
 * Gets the amount of elements the passed set contains.
 * @param set The set to get the actual size of.
 * @param set_size The size of `set`.
 * @returns The number of elements `set` contains.
 */
int get_actual_set_size(OrderedPair set[], int set_size);

/**
 * Checks whether the passed set is a superset of a set in set P.
 * @param set The set to check.
 * @param set_size The size of `set`.
 * @returns `1` if `set` is a superset or `0` if not.
 */
int is_superset_of_set_p_set(OrderedPair set[], int set_size);

/**
 * Updates the contents of set F₃ using the passed sets F₁ and F₂.
 * @param f1 The set F₁ value.
 * @param f2 The set F₂ value.
 * @param f3 The set F₃ value.
 */
void update_set_f3(FSet f1, FSet f2, FSet f3);

/**
 * Prints this board with row and column legends to the console.
 * @param f1 The set F₁ value.
 * @param f2 The set F₂ value.
 */
void print_game_board(FSet f1, FSet f2);
