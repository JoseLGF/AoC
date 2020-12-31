import random

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
def puzzleSolution(instructions):
    # Position and orientation
    shipPose = [[0,0] , 0]
    manhattanDistance = 0
    log(DEBUG, "pose: " + str(shipPose))
    log(DEBUG, "manhattan: " + str(manhattanDistance))
    for instruction in instructions:
        instructionTokens = parseInstruction(instruction)
        shipPose = executeInstruction(shipPose, instructionTokens)
        shipPosition = shipPose[0]
        manhattanDistance = getManhattanDistance(shipPosition)
        log(DEBUG, "Ship's position : " + str(shipPosition))
    print("Day 12 Part 1: " + str(manhattanDistance))

def getManhattanDistance(position):
    position_x  = position[0]
    position_y  = position[1]
    
    return abs(position_x) + abs(position_y)

def parseInstruction(instruction):
    operation = instruction[0]
    value = ""
    for i in range(1, len(instruction)):
        value += instruction[i]
    log(DEBUG, "Op: " + operation + ", val: " + value)
    tokens = [operation, value]
    return tokens

def executeInstruction(shipPose, instructionTokens):
    action                = instructionTokens[0]
    value                 = int(instructionTokens[1])
    shipPosition          = shipPose[0]
    shipOrientation       = shipPose[1]
    shipPosition_x        = shipPosition[0]
    shipPosition_y        = shipPosition[1]
    
    if (action == 'N'):
        shipPosition_y = shipPosition_y + value
    if (action == 'S'):
        shipPosition_y = shipPosition_y - value
    if (action == 'E'):
        shipPosition_x = shipPosition_x + value
    if (action == 'W'):
        shipPosition_x = shipPosition_x - value
    if (action == 'L'):
        shipOrientation  = (shipOrientation + value) % 360
    if (action == 'R'):
        shipOrientation  = (shipOrientation - value) % 360
    if (action == 'F'):
        if (shipOrientation == 0):
            shipPosition_x = shipPosition_x + value
        if (shipOrientation == 90):
            shipPosition_y = shipPosition_y + value
        if (shipOrientation == 180):
            shipPosition_x = shipPosition_x - value
        if (shipOrientation == 270):
            shipPosition_y = shipPosition_y - value
    
    return [[shipPosition_x, shipPosition_y], shipOrientation]
    
def rotate90degLeft(pos_x, pos_y):
    new_pos_x = -pos_y
    new_pos_y =  pos_x

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