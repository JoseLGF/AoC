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
FullInputFileName         = 'input_day8.txt'
SampleInputFileName       = 'sample_day8.txt'#'sample_terminates.txt'
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
def puzzleSolution(instructions):
    accFinalValue = executeProgram(instructions)
    log(LOG_SOLUTION, "Day  8 Part 1: " + str(accFinalValue))

def executeInstruction(instructions, executedInstructions, accumulator, InstructionAddress):
    # Fetch next instruction
    instruction = instructions[InstructionAddress]
    # Mark InstructionAddress as already fetched
    executedInstructions[InstructionAddress] = 1
    # Parse instruction
    tokens = instruction.split(' ')
    operation = tokens[0]
    argument = int(tokens[1])
    if (operation == 'acc'):
        accumulator += argument
        InstructionAddress += 1
    if (operation == 'jmp'):
        InstructionAddress += argument
    if (operation == 'nop'):
        InstructionAddress += 1
    
    log(LOG_DEBUG, instruction + ": Acc:" + str(accumulator) + ", Next: " + str(InstructionAddress))
    return [instructions, executedInstructions, accumulator, InstructionAddress]

def executeProgram(instructions):
    executedInstructions   = []
    accumulator            = 0
    InstructionAddress     = 0
    
    executedInstructions = initializeExecutedInstructions(instructions)
    log(LOG_DEBUG, "******* Executing instructions.")
    while (not executedInstructions[InstructionAddress] == 1):
        [instructions, executedInstructions, accumulator, InstructionAddress] = executeInstruction(instructions, executedInstructions, accumulator, InstructionAddress)
        if (InstructionAddress == len(instructions)):
            log(LOG_INFO, "******* Program terminates with acc = " + str(accumulator))
            return -1
    return accumulator

def initializeExecutedInstructions(lines):
    executedInstructions = [0] * int(len(lines))
    log(LOG_DEBUG, str(executedInstructions))
    return executedInstructions

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