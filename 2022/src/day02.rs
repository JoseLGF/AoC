use crate::helpers;

pub fn solve() {
    let lines = helpers::lines_from_file("./input/day_02.txt");
    println!("Day 02:");
    println!("{}", part_1(&lines));
    println!("{}", part_2(&lines));
}

fn part_1(lines: &Vec<String>) -> u32 {

    let lookup = [[4, 8, 3], [1, 5, 9], [7, 2, 6]];
    let mut total_score = 0;

    for line in lines {
        let his = line.as_bytes()[0] - b'A';
        let mine = line.as_bytes()[2] - b'X';

        total_score += lookup[his as usize][mine as usize];
    }

    return total_score;
}

fn part_2(lines: &Vec<String>) -> u32 {
    let lookup = [[3, 4, 8], [1, 5, 9], [2, 6, 7]];
    let mut total_score = 0;

    for line in lines {
        let his = line.as_bytes()[0] - b'A';
        let mine = line.as_bytes()[2] - b'X';

        total_score += lookup[his as usize][mine as usize];
    }

    return total_score;
}