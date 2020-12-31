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

# -------------------------------------------------
# Global Configurations for the program and testing
# -------------------------------------------------
RunLevel                  = FULLINPUTRUN
FullInputFileName         = 'input.txt'
SampleInputFileName       = 'sample3.txt'
PrintInput                = True
WriteRunResults           = True
RemoveEOLFromInputLines   = True
resultsOutputFileName     = 'out_1.txt'
LogPrintLevel             = DEBUG
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
    log(INFO, strBusIDs)
    
    busIDs = getBusIDsWithOffsets(strBusIDs)
    log(INFO, "Bus IDs: " + str(busIDs))
    
    minimumCommonTime = busIDs[0]
    
    for id in range(1, len(busIDs)):
        Id2 = busIDs[id]
        log(INFO, str(minimumCommonTime) + ", " + str(Id2))
        minimumCommonTime = getMinimumTimeForTwoIDsWithOffsets(minimumCommonTime, Id2)
        log(INFO, "Min: " + str(minimumCommonTime))

def getMinimumTimeForTwoIDsWithOffsets(Id1, Id2):
    busId1  = Id1[0]
    offset1 = Id1[1]
    busId2  = Id2[0]
    offset2 = Id2[1]
    
    iterator1 = 1
    
    generated1 = iterator1 * busId1 + offset1
    
    max_iterations = busId1 * busId2
    satisfied = False
    while(not satisfied):
        log(DEBUG, str(generated1))
        if ((generated1 + offset2) % busId2 == 0):
            satisfied = True
            return [busId1 * busId2, generated1]
        else:
            iterator1 += 1
            generated1 = iterator1 * busId1 + offset1
    
def lcm(a, b):
    return abs(a*b) // math.gcd(a, b)    
    

def getBusIDsWithOffsets(strBusIDs):
    busIDs = []
    busIDsTokens = strBusIDs.rsplit(',')
    log(DEBUG, str(busIDsTokens))
    
    
    for tokenIndex in range(len(busIDsTokens)):
        token = busIDsTokens[tokenIndex]
        if (token == 'x'):
            continue
        else:
            busIDs.append([int(token), tokenIndex])
            currentBusIDOffset = 0
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