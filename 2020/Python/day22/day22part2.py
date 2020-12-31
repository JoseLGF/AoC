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

gameCounter = 0

class RecursiveCombat:
    # All played rounds so far.
    # A Round has the following shape:
    #   [player 1 cards], [Player 2 cards]
    playedRounds = []
    
    player1Cards = []
    player2Cards = []
    
    winningPlayer = -1
    roundCounter  = 0
    thisGameID    = 0
    
    def __init__(self, player1Cards, player2Cards):
        self.playedRounds = []
        
        global gameCounter
        gameCounter += 1
        self.thisGameID = gameCounter
        
        self.player1Cards = player1Cards
        self.player2Cards = player2Cards
        
        log(DEBUG, "=== Game "+ str(self.thisGameID)+" ===")
    
    def calculateWinnerScore(self):
        score = -1
        if not self.isGameFinished():
            score = -1
        else:
            if (len(self.player1Cards) > 0):
                winnerPlayerCards = self.player1Cards
            else:
                winnerPlayerCards = self.player2Cards
                
            # Reverse cards in order to apply increasing multiplier
            winnerPlayerCards = winnerPlayerCards[::-1]
            score = 0
            multiplier = 1
            for card in winnerPlayerCards:
                score += multiplier * card
                multiplier += 1
                
        return score
    
    def isGameFinished(self):
        # If the game winner has already been set by way of insta-win,
        # Return true
        if not self.winningPlayer == -1:
            return True
        
        if (len(self.player1Cards) > 0 and len(self.player2Cards) > 0):
            return False
        else:
            return True
    
    def isRoundRepeated(self):
        # Check if the state of player 1 and player 2 cards has been played
        # before.
        for playedRound in self.playedRounds:
            roundPlayer1Cards = playedRound[0]
            roundPlayer2Cards = playedRound[1]
            if (roundPlayer1Cards == self.player1Cards and 
                roundPlayer2Cards == self.player2Cards):
                return True
        
        return False

    def playGame(self):
        # This function plays rounds until one player wins, then returns the
        # numer of the winning player
        while not self.isGameFinished():
            self.advanceRound()
        
        return self.winningPlayer
        
    def buildDeck(self, p1NumCardsToCopy, p2NumCardsToCopy):
        newP1Deck = []
        newP2Deck = []
        try:
            for index1 in range(p1NumCardsToCopy):
                newP1Deck.append(self.player1Cards[index1])
                
            for index2 in range(p2NumCardsToCopy):
                newP2Deck.append(self.player2Cards[index2])
        except:
            log(ERROR, "Error occured!")
        
        return [newP1Deck, newP2Deck]
    
    def advanceRound(self):
        self.roundCounter += 1
        log(DEBUG, "-- Round " + str(self.roundCounter) + " (Game "+ str(self.thisGameID) +") --")
        log(DEBUG, "Player 1's Deck: " + str(self.player1Cards))
        log(DEBUG, "Player 2's Deck: " + str(self.player2Cards))
        
        # If there was a previous round in this game that had exactly the same 
        # cards in the same order in the same players' decks, the game 
        # instantly ends in a win for player 1.
        if (self.isRoundRepeated()):
            log(DEBUG, "Repeated game: Instawin for p1 ")
            self.winningPlayer = 1
            return

        # Add this round to the playedRounds
        thisRound = self.player1Cards[:],self.player2Cards[:]
        self.playedRounds.append(thisRound)
        
        
        # Each player deals a card
        p1Card = self.player1Cards.pop(0)
        p2Card = self.player2Cards.pop(0)
        log(DEBUG, "Player plays: " + str(p1Card))
        log(DEBUG, "Player plays: " + str(p2Card))
        
        
        p1DeckSize = len(self.player1Cards)
        p2DeckSize = len(self.player2Cards)
        
        # If both players have at least as many cards remaining in their deck
        # as the value of the card they just drew, the winner of the round is
        # determined by playing a new game of Recursive Combat.
        roundWinner = -1
        if (p1Card <= p1DeckSize and p2Card <= p2DeckSize):
            log(PROFILING, "Recurring to create new game...")
            [newp1Deck, newp2Deck] = self.buildDeck(p1Card, p2Card)
            # Assert that the number of cards is monotonically decreasing
            # with every new Deck
            assert len(newp1Deck) <= p1DeckSize , "Deck1 size increased!"
            assert len(newp2Deck) <= p2DeckSize , "Deck1 size increased!"
            log(PROFILING, "Cards: ")
            log(PROFILING, str(newp1Deck) + ", " + str(newp2Deck))
            newGame = RecursiveCombat(newp1Deck, newp2Deck)
            roundWinner = newGame.playGame()
        # Otherwise, at least one player must not have enough cards left in 
        # their deck to recurse; the winner of the round is the player with 
        # the higher-value card.
        else:
            if (p1Card > p2Card):
                roundWinner = 1
            else:
                roundWinner = 2
        
        log(DEBUG, "Player " + str(roundWinner) +" wins round " + str(self.roundCounter) + " of game " + str(self.thisGameID))
        
        # The winner of the round (even if they won the round by winning a 
        # sub-game) takes the two cards dealt at the beginning of the round 
        # and places them on the bottom of their own deck so that the winner's 
        # card is above the other card.
        if roundWinner == 1:
            self.player1Cards.append(p1Card)
            self.player1Cards.append(p2Card)
        else:
            self.player2Cards.append(p2Card)
            self.player2Cards.append(p1Card)
    
        # If collecting cards by winning the round causes a player to have all
        # of the cards, they win, and the game ends.
        if (len(self.player1Cards) == 0):
            self.winningPlayer = 2
        if (len(self.player2Cards) == 0):
            self.winningPlayer = 1


def puzzleSolution1(lines):
    # Extract cards from input
    player1Cards = getPlayer1Cards(lines)
    player2Cards = getPlayer2Cards(lines)
    
    # Build the Recursive combat class
    combat = RecursiveCombat(player1Cards, player2Cards)
    
    combat.playGame()
    
    winningPlayerScore = combat.calculateWinnerScore()
        
    log(SOLUTION, 'Day 22 Part 2: ' + str(winningPlayerScore))
    pass


def getPlayer1Cards(lines):
    player1Cards = []
    for lineIndex in range(1,player2LinesStart-2):
        line = lines[lineIndex]
        card = int(line)
        player1Cards.append(card)
    return player1Cards

def getPlayer2Cards(lines):
    player2Cards = []
    for lineIndex in range(player2LinesStart, len(lines)):
        line = lines[lineIndex]
        card = int(line)
        player2Cards.append(card)
    return player2Cards

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
    
    

