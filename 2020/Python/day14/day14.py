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
LogPrintLevel             = DEBUG
LogWriteLevel             = DEBUG
GenerateRandomInputSample = False
RandomSampleSize          = 500
# -------------------------------------------------

# ----------------------------------------------------
# Functions and globals specific to the current puzzle
# ----------------------------------------------------
def puzzleSolution(lines):
    mask = ''
    addresses = {}
    for line in lines:
        if (line[1] == 'a'):
            mask = getMask(line)
            log(DEBUG, "DEBUG: Mask: " + mask)
        if (line[1] == 'e'):
            value = getValue(line)
            address = getAddress(line)
            log(DEBUG, "DEBUG: Value: " + str(value))
            log(DEBUG, "DEBUG: Address: " + str(address))
            addresses.update(updateValue(value, mask, address))
    
    sumOfValues = 0
    for value in addresses.values():
        log(DEBUG, "Val: " + str(value))
        value_int = binaryStrToIntegerInt(value)
        sumOfValues += value_int
        
        
    
    log(INFO, str(addresses))
    log(INFO, "Final solution: "+ str(sumOfValues))
    pass
 
def binaryStrToIntegerInt(string):
    log(DEBUG, "Converting: " + string)
    reverseStr = reverse(string)
    result = 0
    for i in range(len(reverseStr)):
        result += (int(reverseStr[i]) * (2**(i)) )
    log(DEBUG, "Conversion: " +str(result))
    return result
 
def getMask(line):
    mask = re.search(r"[01X]+", line)
    return mask.group()
    
def getValue(line):
    value = re.search(r"= [0-9]+", line)
    return int(value.group()[2:])
    
def getAddress(line):
    address = re.search(r"\[[0-9]+", line)
    return int(address.group()[1:])

def updateValue(value, mask, address):
    binaryIntStr = intToBinaryStr(value)
    
    # reverse both strings so that they can be reverse
    # iterated and compared
    reverse_mask = reverse(mask)
    reverse_binaryIntStr = reverse(binaryIntStr)
    reverse_valueStr = ""
    for i in range(len(mask)):
        if (i >= len(binaryIntStr)):
            break
        # Apply bitmask
        if (reverse_mask[i] == 'X'):
            reverse_valueStr += reverse_binaryIntStr[i]
        if (reverse_mask[i] == '0'):
            reverse_valueStr += '0'
        if (reverse_mask[i] == '1'):
            reverse_valueStr += '1'
    
    value_str = reverse(reverse_valueStr)
    if (value_str == ''):
        value_str = "0"
    log(DEBUG, "Value str:" + value_str)
    return {address: value_str}
    
    
    pass
    
def intToBinaryStr(value_int):
    binaryStr = ""
    w_value_int = value_int
    while(w_value_int > 0):
        nextBit = w_value_int % 2
        binaryStr += str(nextBit)
        w_value_int = int(w_value_int / 2)
    
    # Add 0s to make 36 digit
    binaryStrLen = len(binaryStr)
    for i in range(binaryStrLen, 36):
        binaryStr += '0'
        
    
    reverseStr = reverse(binaryStr)
    log(DEBUG, str(value_int) + ": " + str(reverseStr))
    return reverseStr

def reverse(s): 
    str = "" 
    for i in s: 
        str = i + str
    return str

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