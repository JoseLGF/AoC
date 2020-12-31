from itertools import combinations


def checkIfTupleOf3NumbersAddTo2020(combination):
    if (combination[0] + combination[1] + combination[2] == 2020):
        print(str(combination[0]) + " * " + str(combination[1]) + " * " + str(combination[2]) + " = ")
        answer = combination[0] * combination[1] * combination[2]
        print("Day 1 part 2 Answer: " + str(answer))
    

# Using readlines()
file = open('Input_day1.txt', 'r')
#file = open('sample_day1.txt', 'r')
Lines = file.readlines()

# Put all numbers in a list
Numbers = []
for line in Lines:
    Numbers.append(int(line.strip()))

# Iterate Numbers array
Numbers_length = len(Numbers)
# Get all the combinations of three elemenents in the array of numbers
combs = combinations(Numbers, 3)

for i in list(combs): 
    checkIfTupleOf3NumbersAddTo2020(i)