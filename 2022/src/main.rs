mod helpers;
mod day01;
mod day02;

fn main() {
    println!("Advent of code 2022 solutions:");

    let lines = helpers::lines_from_file("./input/day_01.txt");

    println!("Day 01:");
    println!("{}", day01::part_1(&lines));
    println!("{}", day01::part_2(&lines));

    let lines2 = helpers::lines_from_file("./input/day_02.txt");
    println!("Day 02:");
    println!("{}", day02::part_1(&lines2));
    println!("{}", day02::part_2(&lines2));
}
