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
WriteRunResults          = False
RemoveEOLFromInputLines  = True
ResultsOutputFileName    = 'out_1.txt'
LogPrintLevel            = SOLUTION
LogWriteLevel            = INFO
# -------------------------------------------------

# ----------------------------------------------------
# Functions and globals specific to the current puzzle
# ----------------------------------------------------
if (RunLevel == SAMPLETESTING):
    player2LinesStart = 8
if (RunLevel == FULLINPUTRUN):
    player2LinesStart = 28

def puzzleSolution1(lines):
    
    player1Cards = getPlayer1Cards(lines)
    player2Cards = getPlayer2Cards(lines)
    
    while (len(player1Cards) > 0 and len(player2Cards) > 0):
        [player1Cards, player2Cards] = advanceRound(player1Cards, player2Cards)
    
    if (len(player1Cards) > 0):
        winningPlayerScore = calculateScore(player1Cards)
    else:
        winningPlayerScore = calculateScore(player2Cards)
        
    log(SOLUTION, 'Day 22 Part 1: ' + str(winningPlayerScore))
    pass

def calculateScore(playerCards):
    score = 0
    multiplier = 1
    for card in playerCards:
        score += multiplier * card
        multiplier += 1
    return score

def advanceRound(player1Cards, player2Cards):
    p1Card = player1Cards.pop()
    p2Card = player2Cards.pop()
    
    if (p1Card > p2Card):
        player1Cards.insert(0, p1Card)
        player1Cards.insert(0, p2Card)
    else:
        player2Cards.insert(0, p2Card)
        player2Cards.insert(0, p1Card)
    
    return [player1Cards, player2Cards]

def getPlayer1Cards(lines):
    player1Cards = []
    for lineIndex in range(1,player2LinesStart-2):
        line = lines[lineIndex]
        card = int(line)
        player1Cards.append(card)
    return player1Cards[::-1]

def getPlayer2Cards(lines):
    player2Cards = []
    for lineIndex in range(player2LinesStart, len(lines)):
        line = lines[lineIndex]
        card = int(line)
        player2Cards.append(card)
    return player2Cards[::-1]

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
    
    

