use std::collections::HashSet;

/// A pair of X and Y values.
pub(crate) type OrderedPair = (i32, i32);
/// A set containing ordered pairs.
pub(crate) type Set = HashSet<OrderedPair>;

/// Gets the amount of sets in set S that are subsets of the passed set.
///
/// # Parameters
/// - `set` - The set to use.
/// # Returns
/// The number of sets that are subsets of `set`.
pub(crate) fn get_set_s_subsets_amount(set: &Set) -> usize {
    let s: [Set; 4] = [
        HashSet::from([(1, 1), (1, 3), (2, 2), (3, 1), (3, 3)]),
        HashSet::from([(4, 4), (4, 6), (5, 5), (6, 4), (6, 6)]),
        HashSet::from([(1, 5), (2, 4), (2, 5), (2, 6), (3, 5)]),
        HashSet::from([(4, 1), (4, 3), (5, 1), (5, 3), (6, 1), (6, 3)]),
    ];
    let mut intersecting_elements_amount: usize = 0;

    for s_set in s {
        if s_set.iter().all(|element| set.contains(element)) {
            intersecting_elements_amount += 1;
        }
    }

    return intersecting_elements_amount;
}

/// Checks whether the passed set is a superset of a set in set P.
///
/// # Parameters
/// - `set` - The set to check.
/// # Returns
/// `true` if `set` is a superset or `false` if not.
pub(crate) fn is_superset_of_set_p_set(set: &Set) -> bool {
    let p: [Set; 2] = [
        HashSet::from([(1, 1), (2, 2)]),
        HashSet::from([(1, 2), (2, 1)]),
    ];

    for p_set in p {
        if p_set.iter().all(|element| set.contains(element)) {
            return true;
        }
    }

    return false;
}

/// Creates a new set F₃ using the passed sets F₁ and F₂.
///
/// # Parameters
/// - `f1` - The set F₁ value.
/// - `f2` - The set F₂ value.
/// # Returns
/// The set F₃ value.
pub(crate) fn create_set_f3(f1: &Set, f2: &Set) -> Set {
    let new_f3: Set = HashSet::from([
        (1, 1),
        (1, 2),
        (1, 3),
        (1, 4),
        (1, 5),
        (1, 6),
        (2, 1),
        (2, 2),
        (2, 3),
        (2, 4),
        (2, 5),
        (2, 6),
        (3, 1),
        (3, 2),
        (3, 3),
        (3, 4),
        (3, 5),
        (3, 6),
        (4, 1),
        (4, 2),
        (4, 3),
        (4, 4),
        (4, 5),
        (4, 6),
        (5, 1),
        (5, 2),
        (5, 3),
        (5, 4),
        (5, 5),
        (5, 6),
        (6, 1),
        (6, 2),
        (6, 3),
        (6, 4),
        (6, 5),
        (6, 6),
    ]);
    let mut f3: Set = new_f3.clone();

    for element in new_f3 {
        if f1.contains(&element) || f2.contains(&element) {
            f3.remove(&element);
        }
    }

    return f3;
}

///  Prints this board with row and column legends to the console.
///
/// # Parameters
/// - `f1` - The set F₁ value.
/// - `f2` - The set F₂ value.
pub(crate) fn print_game_board(f1: &Set, f2: &Set) -> () {
    let max_rows = 6;
    let max_columns = 6;

    for row_number in 0..=max_rows {
        for column_number in 0..=max_columns {
            if row_number == 0 {
                print!("  ");

                if column_number > 0 {
                    print!("{column_number}");

                    if column_number == max_columns {
                        print!("\n");
                    } else {
                        print!(" ");
                    }
                }
            } else {
                if column_number == 0 {
                    print!("{row_number} ");
                } else {
                    let coordinates: OrderedPair = (row_number, column_number);

                    if f1.contains(&coordinates) {
                        print!("| A ");
                    } else if f2.contains(&coordinates) {
                        print!("| B ");
                    } else {
                        print!("|   ");
                    }

                    if column_number == max_columns {
                        println!("|")
                    }
                }
            }
        }

        print!("  ");

        for column_number in 1..=max_columns {
            print!("+---");

            if column_number == max_columns {
                println!("+");
            }
        }
    }

    print!("\n");
}
