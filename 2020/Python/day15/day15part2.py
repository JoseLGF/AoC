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

# -------------------------------------------------
# Global Configurations for the program and testing
# -------------------------------------------------
RunLevel                  = SAMPLETESTING
FullInputFileName         = 'input.txt'
SampleInputFileName       = 'sample.txt'
PrintInput                = True
WriteRunResults           = True
RemoveEOLFromInputLines   = True
resultsOutputFileName     = 'out_1.txt'
LogPrintLevel             = DEBUG
LogWriteLevel             = INFO
GenerateRandomInputSample = False
RandomSampleSize          = 500
# -------------------------------------------------

# ----------------------------------------------------
# Functions and globals specific to the current puzzle
# ----------------------------------------------------
def puzzleSolution(lines):
    numberOfTerms = 10
    ages = [-1 for i in range(numberOfTerms)]
    log(INFO, "Initialized array!.")

    numbers = getStartingNumbers(lines[0])
    index = 0
    # update ages list with intial numbers
    for number in numbers:
        ages[number] = index
        index += 1
    
    # First iteration done manually
    lastNumber = 0
    index += 1
    ages[0] = index
    
    log(DEBUG, "Last nums: " + str(ages))
    # Start iterations
    #lastNumber = numbers[-1]
    while (index <= numberOfTerms):
        if (index % 1000 == 0):
            log(INFO, "Om nom nom..." + str(index))
        log(DEBUG, "Index: " + str(index))
        # process numbers
        
        log(DEBUG, "************Last Number: " + str(lastNumber))
        # if it is the first time the number is spoken
        if (ages[lastNumber] == -1):
            log(DEBUG, "0-Appending 0")
            lastNumber = 0
            # update age
            ages[0] = index
        else:
            lastNumberAge = index - ages[lastNumber]
            log(DEBUG, "N-Appending " + str(lastNumberAge))
            lastNumber = lastNumberAge
            ages[lastNumberAge] = index
            #ages.update({ages[lastNumber]: index-ages[lastNumber]})
        log(DEBUG, "Last nums: " + str(ages))
        index += 1
    
    log(INFO, "Last: " + str(lastNumber))
    pass

def getStartingNumbers(line):
    tokens = line.split(',')
    log(DEBUG, "Tokens: " + str(tokens))
    numbers = []
    for token in tokens:
        numbers.append(int(token))
    return numbers

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

    puzzleSolution(fileLines)

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
        print(message, flush=True)

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