//use std::fs;

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

fn main() {
    println!("Advent of code 2022 solutions:");


    println!("Day 01:");
    
    //let data = fs::read_to_string("./input/example_01.txt").expect("Unable to read file");
    //println!("{}", data);

    let lines = lines_from_file("./input/day_01.txt");
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

    println!("{}", max);
}
