use std::{
    fs::File,
    io::{prelude::*, BufReader},
    path::Path,
};


fn lines_from_file(filename: impl AsRef<Path>) -> Vec<String> {
    let file = File::open(filename).expect("no such file");
    let buf = BufReader::new(file);
    buf.lines()
        .map(|l| l.expect("Could not parse line"))
        .collect()
}

fn day_01_1(lines: Vec<String>) -> u32 {
    let mut max = 0;
    let mut current = 0;
    for line in lines {
        if line.is_empty() {
            if current > max {
                max = current;
            }
            current = 0;
        }
        else {
            let input: u32 = line
            .trim()
            .parse()
            .expect("Wanted a number");

            current += input;
        }
    }
    return max;
}

fn main() {
    println!("Advent of code 2022 solutions:");


    
    let lines = lines_from_file("./input/day_01.txt");

    println!("Day 01:");
    println!("{}", day_01_1(lines));

    
}
