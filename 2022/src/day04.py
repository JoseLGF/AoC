import re

with open('./../input/day_04.txt') as f:
    lines = [line for line in f]

pairs = []

for line in lines:
    pairs.append(re.split('-|,', line.strip()))

#print(pairs)

def is_fully_contained(pair):
    a = int(pair[0])
    b = int(pair[1])
    c = int(pair[2])
    d = int(pair[3])
    if (c >= a and b >= d):
        return True
    if (a >= c and d >= b):
        return True
    return False

def is_overlap(pair):
    a = int(pair[0])
    b = int(pair[1])
    c = int(pair[2])
    d = int(pair[3])
    if (c >= a and b >= c):
        return True
    if (a >= c and d >= a):
        return True
    return False

fully_contained = 0
overlapping = 0
for pair in pairs:
    if (is_fully_contained(pair)):
        fully_contained += 1
    if (is_overlap(pair)):
        overlapping += 1

print(overlapping)
