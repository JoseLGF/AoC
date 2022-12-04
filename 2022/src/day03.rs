use crate::helpers;

use substring::Substring;

pub fn solve() {
    let lines = helpers::lines_from_file("./input/day_03.txt");
    println!("Day 03:");
    println!("{}", part_1(&lines));
    println!("{}", part_2(&lines));
}

fn priority(c: char) -> u32 {
    let cu = c as u32;
    const LOWER_A: u32 = 'a' as u32;
    const LOWER_Z: u32 = 'z' as u32;
    const UPPER_A: u32 = 'A' as u32;
    const UPPER_Z: u32 = 'Z' as u32;

    match cu {
        LOWER_A ..= LOWER_Z => return cu - LOWER_A + 1,
        UPPER_A ..= UPPER_Z => return cu - UPPER_A + 27,
        _ => println!("Error, unexpected value {}", cu),
    }
    return 0;
}

fn part_1(lines: &Vec<String>) -> u32 {

    let mut sum_of_priorities = 0;

    for rucksack in lines {
        // Get elements of each compartment in the rucksack
        let length = rucksack.chars().count();
        let compartment_1 = rucksack.substring(0, length/2);
        let compartment_2 = rucksack.substring(length/2, length);

        // Create bins for character counts of compartment 1
        let mut char_counts: Vec<u8> = Vec::with_capacity(255);
        for _i in 0..255 {
            char_counts.push(0);
        }

        // Count occurences of chars in compartment 1
        for c in compartment_1.chars() {
            char_counts[c as usize] += 1;
        }

        // Check occurences of chars from comp 2 in comp 1
        for c in compartment_2.chars() {
            if char_counts[c as usize] > 0 {
            let prio = priority(c);
            println!("{}: {}", c, prio);
            sum_of_priorities += prio;
            break;
            }
        }
        
    }
    return sum_of_priorities;
}

fn part_2(lines: &Vec<String>) -> u32 {
    return 0;
}