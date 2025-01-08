mod utils;

use std::{collections::HashSet, io::Write};

/// Implements the `NextPlayerMove(pos ∈ F)` function.
fn next_player_move(
    pos: utils::OrderedPair,
    over: bool,
    next: bool,
    f3: &utils::Set,
    good: &mut bool,
    f1: &mut utils::Set,
    f2: &mut utils::Set,
    c1: &mut utils::Set,
    c2: &mut utils::Set,
) -> () {
    let (a, b) = pos;
    // Omitted the floor division because the types are integers (omission also allowed in other languages).
    let c = ((a - 1) / 3) + 1;
    let d = ((b - 1) / 3) + 1;

    if !over && next && f3.contains(&pos) {
        *good = !*good;

        (*f1).insert(pos);
    }

    if !over && !next && f3.contains(&pos) {
        *good = !*good;

        (*f2).insert(pos);
    }

    if !over && *good && next && utils::get_set_s_subsets_amount(f1) > (*c1).len() {
        (*c1).insert((c, d));
    }

    if !over && *good && !next && utils::get_set_s_subsets_amount(f2) > (*c2).len() {
        (*c2).insert((c, d));
    }

    if !over && *good {
        *good = !*good;
    }
}

/// Implements the `GameOver(over)` function.
fn game_over(
    over: bool,
    next: &mut bool,
    c1: &utils::Set,
    c2: &utils::Set,
    result: &mut String,
) -> () {
    if over && *next && c1.len() > 0 && utils::is_superset_of_set_p_set(c1) {
        *result = String::from("A wins");
    }

    if over && !*next && c2.len() > 0 && utils::is_superset_of_set_p_set(c2) {
        *result = String::from("B wins");
    }

    if !over {
        *next = !*next;
    }
}

fn main() -> () {
    let mut f1: utils::Set = HashSet::with_capacity(36);
    let mut f2: utils::Set = HashSet::with_capacity(36);
    let mut f3: utils::Set = HashSet::from([
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
    let mut over = false;
    let mut next = false;
    let mut good = false;
    let mut c1: utils::Set = HashSet::with_capacity(4);
    let mut c2: utils::Set = HashSet::with_capacity(4);
    let mut result = String::from("A and Player B are tied");

    while !over {
        utils::print_game_board(&f1, &f2);

        std::println!("Player {}'s Turn, ", if next { "A" } else { "B" });

        let mut pos: utils::OrderedPair;

        loop {
            std::print!("Input the tile's location {{XY | X = Column, Y = Row}}: ");

            std::io::stdout().flush().expect("Failed to flush stdout.");

            let mut buffer = String::new();

            std::io::stdin()
                .read_line(&mut buffer)
                .expect("Failed to read your input.");

            let given_coordinates = match buffer.trim().parse::<u8>() {
                Ok(coordinates) => coordinates,
                Err(_error) => 0,
            };

            if given_coordinates < 11 || given_coordinates > 66 {
                std::println!("Please input a location within the board.");

                continue;
            }

            pos = (given_coordinates / 10, given_coordinates % 10);

            if !f3.contains(&pos) {
                std::println!("Please input the location of an unoccupied tile.");

                continue;
            }

            break;
        }

        next_player_move(
            pos, over, next, &f3, &mut good, &mut f1, &mut f2, &mut c1, &mut c2,
        );

        f3.remove(&pos);

        over = f3.len() == 0
            || (c1.len() > 0 && utils::is_superset_of_set_p_set(&c1))
            || (c2.len() > 0 && utils::is_superset_of_set_p_set(&c2));

        game_over(over, &mut next, &c1, &c2, &mut result);

        std::println!();
    }

    utils::print_game_board(&f1, &f2);

    std::println!("Player {}!", result);
}
