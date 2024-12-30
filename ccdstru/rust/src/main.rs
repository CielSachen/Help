mod utils;

use std::{collections::HashSet, io};

/// Implements the `NextPlayerMove(pos ∈ F)` function.
///
/// # Parameters
/// - `pos` - The pos element value.
/// - `over` - The over element value.
/// - `next` - The next element value.
/// - `f3` The set F₃ value.
/// - `good` - The good element value.
/// - `f1` - The set F₁ value.
/// - `f2` - The set F₂ value.
/// - `c1` - The set C₁ value.
/// - `c2` - The set C₂ value.
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

    if !over && *good && next && utils::get_set_s_subsets_amount(&*f1) > (*c1).len() {
        (*c1).insert((c, d));
    }

    if !over && *good && !next && utils::get_set_s_subsets_amount(&*f2) > (*c2).len() {
        (*c2).insert((c, d));
    }

    if !over && *good {
        *good = !*good;
    }
}

/// Implements the `GameOver(over)` function.
///
/// # Parameters
/// - `over` - The over element value.
/// - `next` - The next element value.
/// - `c1` - The set C₁ value.
/// - `c2` - The set C₂ value.
/// - `result` - The result element value.
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
    let mut f1: utils::Set = HashSet::new();
    let mut f2: utils::Set = HashSet::new();
    let mut f3: utils::Set = utils::create_set_f3(&f1, &f2);
    let mut over = false;
    let mut next = false;
    let mut good = false;
    let mut c1: utils::Set = HashSet::new();
    let mut c2: utils::Set = HashSet::new();
    let mut result = String::from("A and Player B are tied");

    while !over {
        utils::print_game_board(&f1, &f2);

        if next {
            println!("Player A's Turn,");
        } else {
            println!("Player B's Turn,");
        }

        let mut given_coordinates: i32;
        let mut pos: utils::OrderedPair;

        loop {
            print!("Input the tile's location {{XY | X = Column, Y = Row}}: ");

            io::Write::flush(&mut io::stdout()).expect("Failed to flush stdout.");

            let mut given_input = String::new();

            io::stdin()
                .read_line(&mut given_input)
                .expect("Failed to read the stdin line.");

            given_coordinates = match given_input.trim().parse::<i32>() {
                Ok(input) => input,
                Err(_) => 0,
            };

            if given_coordinates < 11 || given_coordinates > 66 {
                println!("Please input a location within the board.");

                continue;
            }

            pos = (given_coordinates / 10, given_coordinates % 10);

            if !f3.contains(&pos) {
                println!("Please input the location of an unoccupied tile.");

                continue;
            }

            break;
        }

        next_player_move(
            pos, over, next, &f3, &mut good, &mut f1, &mut f2, &mut c1, &mut c2,
        );

        f3 = utils::create_set_f3(&f1, &f2);
        over = f3.len() == 0
            || (c1.len() > 0 && utils::is_superset_of_set_p_set(&c1))
            || (c2.len() > 0 && utils::is_superset_of_set_p_set(&c2));

        game_over(over, &mut next, &c1, &c2, &mut result);

        print!("\n");
    }

    utils::print_game_board(&f1, &f2);

    println!("Player {}!", result);
}
