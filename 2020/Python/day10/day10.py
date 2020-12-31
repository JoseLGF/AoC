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
FullInputFileName         = 'input.txt'
SampleInputFileName       = 'sample_1.txt'
PrintInput                = False
WriteRunResults           = True
resultsOutputFileName     = 'out_1.txt'
LogPrintLevel             = LOG_SOLUTION
LogWriteLevel             = LOG_INFO
GenerateRandomInputSample = False
RandomSampleSize          = 500
# -------------------------------------------------

# ----------------------------------------------------
# Functions and globals specific to the current puzzle
# ----------------------------------------------------
def puzzleSolution(str_numbers):
    ints = parseInts(str_numbers)
    # Append 0 jolt initial outlet
    ints.append(0)
    ints.sort()
    # append the devices joltage (3 highger than highest adapter)
    ints.append(max(ints) + 3)
    log(LOG_DEBUG, "Sorted ints: " + str(ints))
    # Find differences between every adapter stage
    differences = []
    for index in range(len(ints)-1):
        low  = ints[index]
        high = ints[index+1]
        differences.append(high-low)
    log(LOG_INFO, "******* Diffs: " + str(differences))
    num_1s = differences.count(1)
    num_2s = differences.count(2)
    num_3s = differences.count(3)
    log(LOG_INFO, "******* 1s: " + str(num_1s))
    log(LOG_INFO, "******* 2s: " + str(num_2s))
    log(LOG_INFO, "******* 3s: " + str(num_3s))
    final_result = num_1s * num_3s
    
    log(LOG_SOLUTION, "Day 10 Part 1: " + str(final_result))

def parseInts(list_str_ints):
    ints = []
    for string in list_str_ints:
        ints.append(int(string))
        
    log(LOG_DEBUG, " Ints: " + str(ints))
    return ints

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