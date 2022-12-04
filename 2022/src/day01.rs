pub fn part_1(lines: &Vec<String>) -> u32 {
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

pub fn part_2(lines: &Vec<String>) -> u32 {
    let mut calories_counts = Vec::new();
    let mut current = 0;

    for line in lines {
        if line.is_empty() {
            calories_counts.push(current);
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
    
    calories_counts.sort_by(|a, b| b.cmp(a));

    return  calories_counts[0] +
            calories_counts[1] +
            calories_counts[2];
}