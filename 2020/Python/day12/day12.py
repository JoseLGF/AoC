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
    print("Day 12 Part 1: Missing")
        

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

def executeInstruction(pose, shipPosition, instructionTokens):
    action                = instructionTokens[0]
    value                 = int(instructionTokens[1])
    waypointPosition      = pose[0]
    waypointPosition_x    = waypointPosition[0]
    waypointPosition_y    = waypointPosition[1]
    waypointOrientation   = pose[1]
    shipPosition_x        = shipPosition[0]
    shipPosition_y        = shipPosition[1]
    newWaypointPosition_x = waypointPosition_x
    newWaypointPosition_y = waypointPosition_y
    
    if (action == 'N'):
        newWaypointPosition_y = waypointPosition_y + value
    if (action == 'S'):
        newWaypointPosition_y = waypointPosition_y - value
    if (action == 'E'):
        newWaypointPosition_x = waypointPosition_x + value
    if (action == 'W'):
        newWaypointPosition_x = waypointPosition_x - value
    if (action == 'L'):
        waypointOrientation  = value % 360
        if (waypointOrientation == 0):
            pass
        if (waypointOrientation == 90):
            newWaypointPosition_x = -waypointPosition_y
            newWaypointPosition_y = waypointPosition_x
        if (waypointOrientation == 180):
            newWaypointPosition_x = -waypointPosition_x
            newWaypointPosition_y = -waypointPosition_y
        if (waypointOrientation == 270):
            newWaypointPosition_x = waypointPosition_y
            newWaypointPosition_y = -waypointPosition_x
    if (action == 'R'):
        waypointOrientation  = value % 360
        if (waypointOrientation == 0):
            pass
        if (waypointOrientation == 90):
            newWaypointPosition_x = waypointPosition_y
            newWaypointPosition_y = -waypointPosition_x
        if (waypointOrientation == 180):
            newWaypointPosition_x = -waypointPosition_x
            newWaypointPosition_y = -waypointPosition_y
        if (waypointOrientation == 270):
            newWaypointPosition_x = -waypointPosition_y
            newWaypointPosition_y = waypointPosition_x
    if (action == 'F'):
        if (not waypointOrientation in [0, 90, 180, 270]):
            log(ERROR, "Error: Invalid orientation: " + str(waypointOrientation))
        else:
            shipPosition_x = shipPosition_x + (waypointPosition_x * value)
            shipPosition_y = shipPosition_y + (waypointPosition_y * value)
    
    return [[[newWaypointPosition_x, newWaypointPosition_y], waypointOrientation], [shipPosition_x, shipPosition_y]]
    
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