import random
import math
import re

# Run types
PROBETESTING  = 0
SAMPLETESTING = 1
FULLINPUTRUN  = 3
# Log levels
DEBUG     = 0
PROFILING = 1
INFO      = 2
WARNING   = 3
ERROR     = 4
SOLUTION  = 5
# Puzzle partition
PART1     = 1
PART2     = 2

# -------------------------------------------------
# Global Configurations for the program and testing
# -------------------------------------------------
RunLevel                  = FULLINPUTRUN
puzzle_part               = PART1
FullInputFileName         = 'input.txt'
SampleInputFileName       = 'sample.txt'
PrintInput                = False
WriteRunResults           = True
RemoveEOLFromInputLines   = True
resultsOutputFileName     = 'out_1.txt'
LogPrintLevel             = SOLUTION
LogWriteLevel             = INFO
GenerateRandomInputSample = False
RandomSampleSize          = 500
# -------------------------------------------------

# ----------------------------------------------------
# Functions and globals specific to the current puzzle
# ----------------------------------------------------
def puzzleSolution1(lines):
    cardSubjectNumber = 7
    doorSubjectNumber = 7
    
    cardPublicKey = int(lines[0])
    doorPublicKey = int(lines[1])
    
    cardLoopSize = calculateLoopSize(cardSubjectNumber, cardPublicKey)
    log(INFO, "Card Loop Size: " + str(cardLoopSize))
    
    doorLoopSize = calculateLoopSize(doorSubjectNumber, doorPublicKey)
    log(INFO, "Door Loop Size: " + str(doorLoopSize))
    
    encriptionKeyFromCard = transform(cardPublicKey, doorLoopSize)
    log(INFO, "Encription key Calculated from card: " + str(encriptionKeyFromCard))

    encriptionKeyFromDoor = transform(doorPublicKey, cardLoopSize)
    log(INFO, "Encription key Calculated from door: " + str(encriptionKeyFromDoor))
    
    log(SOLUTION, "Day 25 Part 1: " + str(encriptionKeyFromDoor))

def calculateLoopSize(subjectNumber, publicKey):
    value = 1
    loopSize = 0
    while(not value == publicKey):
        loopSize += 1
        value *= subjectNumber
        value %= 20201227
    return loopSize

def transform(subjectNumber, loopSize):
    value = 1
    for i in range(loopSize):
        value *= subjectNumber
        value %= 20201227
    return value

def test():
    cardSubjectNumber = 7
    doorSubjectNumber = 7
    
    cardLoopSize = 8
    doorLoopSize = 11
        
    cardPublicKey = transform(cardSubjectNumber, cardLoopSize)
    log(INFO, "Card public key:" + str(cardPublicKey))
    
    doorPublicKey = transform(doorSubjectNumber, doorLoopSize)
    log(INFO, "Door public key:" + str(doorPublicKey))
    
    encriptionKey = transform(cardPublicKey, doorLoopSize)
    log(INFO, "Encription key: " + str(encriptionKey))
    
    testCardLoopSize = calculateLoopSize(cardSubjectNumber, cardPublicKey)
    log(INFO, "Card Loop Size: " + str(testCardLoopSize))
    
    testDoorLoopSize = calculateLoopSize(doorSubjectNumber, doorPublicKey)
    log(INFO, "Door Loop Size: " + str(testDoorLoopSize))
    
def puzzleSolution2(lines):
    pass

# ------------------
# Global definitions
# ------------------
logStr = ""

def main():
    # Probe testing
    if (RunLevel == PROBETESTING):
        log(INFO, "******* Running Probe Testing")

    fileLines = readRawLines(RemoveEOLFromInputLines)

    if (GenerateRandomInputSample):
        fileLines = generateRandomInputSubset(fileLines)

    if (puzzle_part == PART1):
        log(INFO, "******* Solution to part 1:")
        puzzleSolution1(fileLines)
    if (puzzle_part == PART2):
        log(INFO, "******* Solution to part 2:")
        puzzleSolution2(fileLines)
       
# Implement this function to write specific results to a text file
def writeRunResults(seatIDs):
    log(INFO, "******* Writing results to specified output file")
    s = ""
    for id in seatIDs:
        s += str(id) + "\n"

    with open(resultsOutputFileName, "w") as file:
        # Writing data to a file
        file.write(s)

# Implement this function. Currently only takes random lines.
def generateRandomInputSubset(input_lines):
    RandomLines = []
    for i in range(RandomSampleSize):
        RandomLines.append(random.choice(input_lines))

def readRawLines(stripEOL=False):

    if (RunLevel == SAMPLETESTING):
        filename = SampleInputFileName
    if (RunLevel == FULLINPUTRUN):
        filename = FullInputFileName

    log(INFO, "******* Reading from file " + filename)
    with open(filename,'r') as file:
        raw_lines = file.readlines()

    # remove EOL from lines
    stripped_lines = []
    for line in raw_lines:
        stripped_lines.append(line.rstrip('\n'))

    if (PrintInput):
        log(INFO, "******* Input:")
        for line in raw_lines:
            log(INFO, line.rstrip("\n"))
        log(INFO, "")
    log(INFO, "******* Read " + str(len(raw_lines)) + " lines.")
   
    if (stripEOL):
        return stripped_lines
    else:
        return raw_lines

def log(type, message):
    global logStr

    if (not type < LogPrintLevel):
        print(message)

    if (not type < LogWriteLevel):
        logStr += message + "\n"

def writeLogFile():
    global logStr
    log(INFO, "******* Writing results to run_logfile.txt.")
    with open("run_logfile.txt", "w") as file:
        # Writing data to a file
        file.write(logStr)

if __name__ == "__main__":
    main()
    writeLogFile()