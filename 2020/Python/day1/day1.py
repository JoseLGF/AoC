file = open('Input_day1.txt', 'r')
#file = open('sample_day1.txt', 'r') 
Lines = file.readlines()


Numbers = []
for line in Lines:
    Numbers.append(int(line.strip()))

for number in Numbers:
    requiredNumber = 2020 - number
    if requiredNumber in Numbers:
        #print("Found the numbers:" + str(requiredNumber) + ", " + str(number))
        print("Day  1 part 1: " + str(requiredNumber*number))
        break