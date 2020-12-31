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
RunLevel                  = FULLINPUTRUN
FullInputFileName         = 'input.txt'
SampleInputFileName       = 'sample.txt'
PrintInput                = True
WriteRunResults           = True
RemoveEOLFromInputLines   = True
resultsOutputFileName     = 'out_1.txt'
LogPrintLevel             = INFO
LogWriteLevel             = INFO
GenerateRandomInputSample = False
RandomSampleSize          = 500
# -------------------------------------------------

# ----------------------------------------------------
# Functions and globals specific to the current puzzle
# ----------------------------------------------------
def puzzleSolution(lines):
    numbers = getStartingNumbers(lines[0])
    ages = {}
    index = 1
    # update ages dict with intial numbers
    for number in numbers:
        ages.update({number : [index,index]})
        index += 1
    log(DEBUG, "Last nums: " + str(ages))
    
    
    while (len(numbers) < 2020):
        
        log(DEBUG, "Index: " + str(index))
        # process numbers
        lastNumber = numbers[-1]
        log(DEBUG, "Number " + str(lastNumber))
        # if it is the first time the number is spoken
        if (numbers.count(lastNumber) == 1):
            log(DEBUG, "0-Appending 0")
            numbers.append(0)
            # update age
            ages[0][0] = ages[0][1]
            ages[0][1] = index
        else:
            lastNumberAge = ages[lastNumber][1]-ages[lastNumber][0]
            log(DEBUG, "N-Appending " + str(lastNumberAge))
            numbers.append(lastNumberAge)
            if lastNumberAge in ages:
                ages[lastNumberAge][0] = ages[lastNumberAge][1]
                ages[lastNumberAge][1] = index
            else:
                ages.update({lastNumberAge: [index,index]})
            #ages.update({ages[lastNumber]: index-ages[lastNumber]})
        log(DEBUG, "numbers  : " + str(numbers))
        log(DEBUG, "Last nums: " + str(ages))
        index += 1
    
    log(INFO, "Last: " + str(numbers[-1]))
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