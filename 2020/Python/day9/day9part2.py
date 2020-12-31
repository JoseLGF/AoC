import random

# Run types
PROBETESTING  = 0
SAMPLETESTING = 1
FULLINPUTRUN  = 3
# Log levels
LOG_DEBUG     = 0
LOG_PROFILING = 1
LOG_INFO      = 2
LOG_WARNING   = 3
LOG_ERROR     = 4
LOG_SOLUTION  = 5

# -------------------------------------------------
# Global Configurations for the program and testing
# -------------------------------------------------
RunLevel                  = FULLINPUTRUN
FullInputFileName         = 'input_day9.txt'
SampleInputFileName       = 'sample_preamble5.txt'#'sample_terminates.txt'
PrintInput                = False
WriteRunResults           = True
resultsOutputFileName     = 'out_1.txt'
LogPrintLevel             = LOG_SOLUTION
LogWriteLevel             = LOG_ERROR
GenerateRandomInputSample = False
RandomSampleSize          = 500
# -------------------------------------------------

# ----------------------------------------------------
# Functions and globals specific to the current puzzle
# ----------------------------------------------------
def puzzleSolution(str_numbers):
    numbers = parseNumbers(str_numbers)
    preambleSize = 25
    tail = []
    number = -1
    invalidNumbers = []
    
    
    for index in range(preambleSize, len(numbers)):
        number = numbers[index]
        log(LOG_INFO, "******* Checking number: " + str(number))
        log(LOG_INFO, "******* tail for index: " + str(index))
        tail = calculateTailGivenIndex(numbers, index, preambleSize)
        log(LOG_INFO, str(tail))
        isValid = isNextNumberValid(number, tail)
        if (not isValid):
            invalidNumbers.append(number)
    log(LOG_INFO, "******* Invalid numbers: " + str(invalidNumbers))
    
    invalidNumber = invalidNumbers[0]
    log(LOG_SOLUTION, "Day  9 Part 1: " + str(invalidNumber))
    
    log(LOG_INFO, "******* Generating contiguous sets:")
    validContiguousSets = []
    # generate contiguous sets
    for indexLeft in range(len(numbers)):
        for indexRight in range(indexLeft+1, len(numbers)):
            contiguousSet = numbers[indexLeft:indexRight+1]
            log(LOG_DEBUG, str(contiguousSet))
            if (sum(contiguousSet) == invalidNumber):
                validContiguousSets.append(contiguousSet)
                log (LOG_INFO, "Found sum with elements: " + str(contiguousSet))
    
    log(LOG_INFO, str(validContiguousSets))
    minNum = min(validContiguousSets[0])
    maxNum = max(validContiguousSets[0])
    solution = minNum + maxNum
    log(LOG_SOLUTION, "Day  9 Part 2: " + str(solution))

def calculateTailGivenIndex(numbers, index, preambleSize):
    if (index < preambleSize):
        log(LOG_ERROR, "******* ERROR, invalid index.")
        return []
    
    tail = []
    for i in range(preambleSize):
        tail.append(numbers[index-i-1])
    return tail

def parseNumbers(str_numbers):
    numbers = []
    for line in str_numbers:
        numbers.append(int(line.rstrip('\n')))
    return numbers

def isNextNumberValid(number, tail):
    for tailIndex1 in range(len(tail)):
        for tailIndex2 in range(len(tail)):
            # Avoid the same number
            if (tailIndex1 == tailIndex2):
                log(LOG_DEBUG, "skipping same indices...")
                continue
            number1 = tail[tailIndex1]
            number2 = tail[tailIndex2]
            log(LOG_DEBUG, "Checking " + str(number1) + " and " + str(number2))
            if (number1 + number2 == number):
                log(LOG_DEBUG, "Number is valid")
                return True
    log(LOG_INFO, "Number " + str(number) + " is not valid!")
    return False


# ------------------
# Global definitions
# ------------------
logStr = ""

def main():
    # Probe testing
    if (RunLevel == PROBETESTING):
        log(LOG_INFO, "******* Running Probe Testing")

    fileLines = readRawLines()

    if (GenerateRandomInputSample):
        fileLines = generateRandomInputSubset(fileLines)

    puzzleSolution(fileLines)

# Implement this function to write specific results to a text file
def writeRunResults(seatIDs):
    log(LOG_INFO, "******* Writing results to specified output file")
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

def readRawLines():

    if (RunLevel == SAMPLETESTING):
        filename = SampleInputFileName
    if (RunLevel == FULLINPUTRUN):
        filename = FullInputFileName

    log(LOG_INFO, "******* Reading from file " + filename)
    with open(filename,'r') as file:
        raw_lines = file.readlines()

    if (PrintInput):
        log(LOG_INFO, "******* Raw input:")
        for line in raw_lines:
            log(LOG_INFO, line.rstrip("\n"))
        log(LOG_INFO, "")
        log(LOG_INFO, "******* Read " + str(len(raw_lines)) + " lines.")
    return raw_lines

def log(type, message):
    global logStr

    if (not type < LogPrintLevel):
        print(message)

    if (not type < LogWriteLevel):
        logStr += message + "\n"

def writeLogFile():
    global logStr
    log(LOG_INFO, "******* Writing results to run_logfile.txt.")
    with open("run_logfile.txt", "w") as file:
        # Writing data to a file
        file.write(logStr)

if __name__ == "__main__":
    main()
    writeLogFile()