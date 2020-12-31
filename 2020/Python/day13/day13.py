import random
import math

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

# -------------------------------------------------
# Global Configurations for the program and testing
# -------------------------------------------------
RunLevel                  = FULLINPUTRUN
FullInputFileName         = 'input.txt'
SampleInputFileName       = 'sample.txt'
PrintInput                = False
WriteRunResults           = True
RemoveEOLFromInputLines   = True
resultsOutputFileName     = 'out_1.txt'
LogPrintLevel             = SOLUTION
LogWriteLevel             = DEBUG
GenerateRandomInputSample = False
RandomSampleSize          = 500
# -------------------------------------------------

# ----------------------------------------------------
# Functions and globals specific to the current puzzle
# ----------------------------------------------------
def puzzleSolution(lines):
    
    departureTimestamp = int(lines[0])
    log(INFO, "Earliest departure time: " + str(departureTimestamp))
    strBusIDs = lines[1]
    log(DEBUG, strBusIDs)
    
    busIDs = getBusIDsFromStr(strBusIDs)
    log(DEBUG, "Bus IDs: " + str(busIDs))
    
    smallestTimestamps = []
    for busID in busIDs:
        smallestTimestamps.append(getSmallestTimestampForID(departureTimestamp, busID))
    
    #print("Smallest available bus ID : " + str(min(smallestTimestamps)))
    
    minutesToWait = min(smallestTimestamps) - departureTimestamp
    log(INFO, " Time to wait: " + str(minutesToWait))
    log(SOLUTION, "day 13 Part 1: TODO")
    pass

def getSmallestTimestampForID(departureTimestamp, busID):
    integerPart = math.ceil(departureTimestamp/busID)
    smallestTimestamp = busID * integerPart
    log(DEBUG, str(busID) + ": " + str(integerPart) + "->" + str(smallestTimestamp))
    return smallestTimestamp

def getBusIDsFromStr(strBusIDs):
    busIDs = []
    busIDsTokens = strBusIDs.rsplit(',')
    log(DEBUG, str(busIDsTokens))
    for token in busIDsTokens:
        if (token == 'x'):
            continue
        else:
            busIDs.append(int(token))
    return busIDs

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