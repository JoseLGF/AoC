# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import random
import math
import re
from itertools import permutations

# Run levels
PROBETESTING  = 0
SAMPLETESTING = 1
FULLINPUTRUN  = 2

# Log Levels
DEBUG     = 0
PROFILING = 1
INFO      = 2
WARNING   = 3
ERROR     = 4
SOLUTION  = 5

# Puzzle part selection
PART1 = 1
PART2 = 2

# -------------------------------------------------
# Global configurations for the program and testing
# -------------------------------------------------
RunLevel                 = FULLINPUTRUN
Puzzle_part              = PART1
FullInputFileName        = 'input.txt'
SampleInputFileName      = 'sample.txt'
PrintInput               = False
WriteRunResults          = True
RemoveEOLFromInputLines  = True
ResultsOutputFileName    = 'out_1.txt'
LogPrintLevel            = SOLUTION
LogWriteLevel            = INFO
# -------------------------------------------------

# ----------------------------------------------------
# Functions and globals specific to the current puzzle
# ----------------------------------------------------
numberOfMoves = 100

def puzzleSolution1(lines):
    # cups : List of integers, parsed from the only line in the input.
    cups = getCups(lines)
    log(INFO, "Cups: " + str(cups))
    
    currentCupIndex = 0
    for move in range(numberOfMoves):
        log(DEBUG, "-- Move " + str(move+1) +" --")
        [cups, currentCupIndex] = executeMove(cups, currentCupIndex)
    
    number1Index = cups.index(1)
    cupsStr = ""
    for i in range(len(cups)):
        index = (number1Index+i+1)%len(cups)
        cupsStr += str(cups[index])
    
    log(SOLUTION, "Day 23 Part 1: " + cupsStr)

def executeMove(cups, currentCupIndex):
    log(DEBUG, "Cups :" + str(cups))
    log(DEBUG, "Current cup index:" + str(currentCupIndex))
    
    # Calculate pickup
    pickUp = []
    pickUpIndices = range(currentCupIndex+1,currentCupIndex+1+3)
    wrappedIndex = -1
    for index in pickUpIndices:
        if index >= 9:
            wrappedIndex = index % 9
        indexMod9 = index % 9
        pickUp.append(cups[indexMod9])
    log(DEBUG, "Pickup: " + str(pickUp))
    cupsAfterRemovePickup = cups[wrappedIndex+1:currentCupIndex+1] + cups[currentCupIndex+1+3:]
    
    
    # Calculate destination
    currentCupLabel = cups[currentCupIndex]
    log(DEBUG, "Current cup:" + str(currentCupLabel))
    destination = currentCupLabel - 1
    if destination == 0:
        destination = 9
    while (destination in pickUp):
        if destination == 1:
            destination = 9
        else:
            destination -= 1
    log(DEBUG, "Destination:" + str(destination))
    destinationIndex = cupsAfterRemovePickup.index(destination)
    
    # Build the new cups formation
    # All elements before and including the current cup in the removed cups
    elementsBeforeAndIncludingCurrentCup = cupsAfterRemovePickup[0:destinationIndex+1]
    newCups = elementsBeforeAndIncludingCurrentCup
    # The pickup
    newCups += pickUp
    # Lastly, whichever remaining elements
    remainingElements = cupsAfterRemovePickup[destinationIndex+1:]
    newCups += remainingElements
    
    # Calculate the new current cup index
    newCurrentCupIndex = newCups.index(currentCupLabel)+1
    if (newCurrentCupIndex==9):
        newCurrentCupIndex = 0
    return [newCups, newCurrentCupIndex]

def getCups(lines):
    line = lines[0]
    cups = []
    for index in range(len(line)):
        cup = int(line[index])
        cups.append(cup)
    return cups

def puzzleSolution2(lines):
    pass

# ------------------
# Global definitions
# ------------------
logStr = ""

def main():
    if (RunLevel == PROBETESTING):
        log(INFO, "******* Running Probe Testing...")
        
    fileLines = readRawLines(RemoveEOLFromInputLines)
        
    if (Puzzle_part == PART1):
        log(INFO, "******* Solution to part 1:")
        puzzleSolution1(fileLines)
    
    if (Puzzle_part == PART2):
        log(INFO, "******* Solution to part 2:")
        puzzleSolution2(fileLines)

def readRawLines(stripEOL=False):
    fileName = ""
    if (RunLevel == SAMPLETESTING):
        fileName = SampleInputFileName
    if (RunLevel == FULLINPUTRUN):
        fileName = FullInputFileName
    
    log(INFO, "******* Reading from file " + fileName)
    with open(fileName, 'r') as file:
        raw_lines = file.readlines()
    
    # Remove EOL from lines
    strippedLines = []
    for line in raw_lines:
        strippedLines.append(line.rstrip('\n'))
        
    if (PrintInput):
        log(INFO, "******* Input:")
        for line in raw_lines:
            log(INFO, line.rstrip('\n'))
        log(INFO,"")
    log(INFO, "******* Read " + str(len(raw_lines)) + " lines.")
    
    if (stripEOL):
        return strippedLines
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
    log(INFO, "******* Writing results to run_logfile.txt")
    with open("run_logfile.txt", 'w') as file:
        # Write data to logfile
        file.write(logStr)
        
if __name__ == "__main__":
    main()
    writeLogFile()
    
    

