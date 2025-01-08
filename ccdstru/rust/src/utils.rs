use std::collections::HashSet;

/// A pair of X and Y values.
pub type OrderedPair = (u8, u8);
/// A set containing ordered pairs.
pub type Set = HashSet<OrderedPair>;

/// Gets the amount of sets in set S that are subsets of the passed set.
pub fn get_set_s_subsets_amount(set: &Set) -> usize {
    let s: [Set; 4] = [
        HashSet::from([(1, 1), (1, 3), (2, 2), (3, 1), (3, 3)]),
        HashSet::from([(4, 4), (4, 6), (5, 5), (6, 4), (6, 6)]),
        HashSet::from([(1, 5), (2, 4), (2, 5), (2, 6), (3, 5)]),
        HashSet::from([(4, 1), (4, 3), (5, 1), (5, 3), (6, 1), (6, 3)]),
    ];
    let mut subsets_amount: usize = 0;

    for s_set in s {
        if s_set.is_subset(&set) {
            subsets_amount += 1;
        }
    }

    return subsets_amount;
}

/// Checks whether the passed set is a superset of a set in set P.
pub fn is_superset_of_set_p_set(set: &Set) -> bool {
    let p: [Set; 2] = [
        HashSet::from([(1, 1), (2, 2)]),
        HashSet::from([(1, 2), (2, 1)]),
    ];

    for p_set in p {
        if set.is_superset(&p_set) {
            return true;
        }
    }

    return false;
}

/// Prints this board with row and column legends to the console.
pub fn print_game_board(f1: &Set, f2: &Set) -> () {
    let maximum_rows = 6;
    let maximum_columns = 6;

    for row_number in 0..=maximum_rows {
        for column_number in 0..=maximum_columns {
            if row_number == 0 {
                std::print!("  ");

                if column_number > 0 {
                    std::print!("{}", column_number);

                    if column_number == maximum_columns {
                        std::println!();
                    } else {
                        std::print!(" ");
                    }
                }
            } else if column_number == 0 {
                std::print!("{} ", row_number);
            } else {
                let coordinates: OrderedPair = (column_number, row_number);

                if f1.contains(&coordinates) {
                    std::print!("| A ");
                } else if f2.contains(&coordinates) {
                    std::print!("| B ");
                } else {
                    std::print!("|   ");
                }

                if column_number == maximum_columns {
                    std::println!("|");
                }
            }
        }

        std::print!("  ");

        for column_number in 1..=maximum_columns {
            std::print!("+---");

            if column_number == maximum_columns {
                std::println!("+");
            }
        }
    }

    std::println!();
}
