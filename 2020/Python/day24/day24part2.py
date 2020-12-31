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
    log(SOLUTION, "Day 24 part 2: TODO")
    return
    # If a tile is not in tiles, it means it was never flipped (white)
    # If a tile appears with an odd  value, it means it is black (flipped)
    # If a tile appears with an even value, it means it is white (not flipped)
    tiles = {}
    for line in lines:
        tile = identifyTileGivenByLine(line)
        if not tile in tiles:
            tiles[tile] = 1
        else:
            tiles[tile] += 1
    
    black_tiles = 0
    for tile in tiles:
        if (tiles[tile] % 2 == 1):
            black_tiles += 1
    
    # The tiles to be analyzed in each iteration are the black tiles, as well as
    # all their respective neighbors
    
    
def getTileNeighbors(x, y):
    neighbors = []
    neighbors.append([x+2, y  ])
    neighbors.append([x+1, y+1])
    neighbors.append([x-1, y+1])
    neighbors.append([x-2, y  ])
    neighbors.append([x+1, y-1])
    neighbors.append([x-1, y-1])
    return neighbors
    
def identifyTileGivenByLine(line):
    tileX = 0
    tileY = 0
    index = 0
    while(index < len(line)):
        direction = line[index]
        if   (direction == 'e'):
            tileX += 2
            index += 1
        elif (direction == 'w'):
            tileX -= 2
            index += 1
        elif (direction == 'n'):
            tileY += 1
            direction2 = line[index+1]
            if (direction2 == 'w'):
                tileX -= 1
            elif(direction2 == 'e'):
                tileX += 1
            else:
                log(ERROR, "Parsing error!")
            index += 2
        elif (direction == 's'):
            tileY -= 1
            direction2 = line[index+1]
            if (direction2 == 'w'):
                tileX -= 1
            elif(direction2 == 'e'):
                tileX += 1
            else:
                log(ERROR, "Parsing error!")
            index += 2
        else:
            log(ERROR, "Parsing error!")
    
    return (tileX, tileY)
    
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