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
# Puzzle partition
PART1     = 1
PART2     = 2

# -------------------------------------------------
# Global Configurations for the program and testing
# -------------------------------------------------
RunLevel                  = FULLINPUTRUN
puzzle_part               = PART2
FullInputFileName         = 'input.txt'
SampleInputFileName       = 'sample.txt'
PrintInput                = False
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
def puzzleSolution1(lines):
    log(INFO, "Fields:")
    fields = getFieldsInfo(lines)
    log(INFO, str(fields))
    
    log(INFO, "Valid values:")
    validValues = getAllValidRanges(fields)
    log(INFO, str(validValues))
    
    log(INFO, "Nearby tickets:")
    nearbyTickets = getNearbyTickets(lines)
    log(INFO, str(nearbyTickets[0]))
    
    log(INFO, "Ticket scanning error rate for Nearby Tickets:")
    nearbyScanningErrorRate = getTicketScanningErrorRate(nearbyTickets, validValues)
    log(INFO, str(nearbyScanningErrorRate))
    
    log(INFO, "Discarding invalid tickets.")
    log(INFO, "Valid tickets:")
    validTickets = discardInvalidTickets(nearbyTickets, validValues)
    log(INFO, str(validTickets))
    
    # valid Tickets required for part 2
    return validTickets


def puzzleSolution2(lines):
    log(INFO, "Obtaining valid tickets...")
    validTickets = puzzleSolution1(lines)
    
    log(INFO, "Getting all field names:")
    fields = getFieldsInfo(lines)
    fieldNames = getFieldNamesFromFieldInfo(fields)
    log(INFO, str(fieldNames))
    
    log(INFO, "Fields Ranges:")
    fieldsRanges = getFieldRangesFromFieldInfo(fields)
    log(INFO, str(fieldsRanges))
    
    log(INFO, "Matching fields with ranges")
    possibleFields = {}
    
        
    
    possibleFields = [[], [], [], [], [],[], [], [], [], [],[], [], [], [], [],[], [], [], [], []]
    possibleFieldsIDs = [[], [], [], [], [],[], [], [], [], [],[], [], [], [], [],[], [], [], [], []]
    for ticketTokenIndex in range(len(fieldNames)):
        log(DEBUG, "Token " + str(ticketTokenIndex))
        timesThisTokenHasBeenUpdated = 0
        for ticketFieldIndex in range(len(fields)):
            currentRange = fieldsRanges[ticketFieldIndex]
            currentFieldName = fieldNames[ticketFieldIndex]
            log(DEBUG, str(currentFieldName) + str(currentRange))
            isThisFieldValid = True
            for validTicketIndex in range(len(validTickets)):
                ticket = validTickets[validTicketIndex]
                number = int(ticket[ticketTokenIndex])
                log(DEBUG, "checking " + str(number))
                if ((number < currentRange[0] or number > currentRange[1] ) and 
                    (number < currentRange[2] or number > currentRange[3] ) ):
                    log(DEBUG, "Number " + str(number) + " is outside of range. Discarding " + currentFieldName)
                    isThisFieldValid = False
            if isThisFieldValid:
                log(DEBUG, "Adding " + currentFieldName + " for token " + str(ticketTokenIndex))
                possibleFields[ticketTokenIndex].append( currentFieldName)
                possibleFieldsIDs[ticketTokenIndex].append( ticketFieldIndex)
                timesThisTokenHasBeenUpdated += 1
                if (timesThisTokenHasBeenUpdated > 1):
                    log (WARNING, "******* Warning, token updated multiple times")
    
    log(INFO, str(possibleFields))
    log(INFO, str(possibleFieldsIDs))
    
    for possibleFieldsID in possibleFieldsIDs:
        log(INFO, str(possibleFieldsID))
    
    
        
    
def getFieldRangesFromFieldInfo(fields):
    fieldRangesList = []
    regex = r"[0-9]+"
    for field in fields:
        fieldRanges = re.findall(regex, field)
        fieldRanges_Int = []
        for fieldRange in fieldRanges:
            fieldRanges_Int.append(int(fieldRange))
        fieldRangesList.append(fieldRanges_Int)
    
    return fieldRangesList
    
def getFieldNamesFromFieldInfo(fields):
    fieldsStr = ""
    for field in fields:
        fieldsStr += field
    regex = r"[a-z ]+:"
    fieldNames = re.findall(regex, fieldsStr)
    return fieldNames
    

def discardInvalidTickets(Tickets, validRanges):
    validTickets = []
    for ticket in Tickets:
        isTicketValid = True
        for value_str in ticket:
            value = int(value_str)
            if (not isValueValidInRanges(value, validRanges)):
                isTicketValid = False
        if (isTicketValid):
            validTickets.append(ticket)
    return validTickets

def isValueValidInRanges(value, ranges):
    for range in ranges:
        if (value >= range[0] and value <= range[1]):
            return True
    return False

def getTicketScanningErrorRate(Tickets, validRanges):
    rate = 0
    for ticket in Tickets:
        for value_str in ticket:
            value = int(value_str)
            if (not isValueValidInRanges(value, validRanges)):
                rate += value
    return rate

def getNearbyTickets(lines):
    if (RunLevel == SAMPLETESTING):
        startingLine = 8
    if (RunLevel == FULLINPUTRUN):
        startingLine = 25
    
    out = []
    for index in range(startingLine, len(lines)):
        out.append(lines[index].rsplit(','))
    
    return out

def convertRangeStringToListOfInt(range):
    range_int = []
    regex = r"[0-9]+"
    numbers = re.findall(regex, range)
    for number_str in numbers:
        range_int.append(int(number_str))
    return range_int

def getAllValidRanges(fields):
    validRanges = []
    for field in fields:
        regex = r"[0-9]+-[0-9]+"
        #validRanges = [validRanges, re.findall(regex, field)]
        ranges = re.findall(regex, field)
        for range in ranges:
            validRanges.append(convertRangeStringToListOfInt(range))
    return validRanges

def getFieldsInfo(lines):
    out = []
    for line in lines:
        if (line == ''):
            break
        out.append(line)
    return out

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

    if (puzzle_part == PART1):
        log(INFO, "******* Solution to part 1:")
        puzzleSolution1(fileLines)
    if (puzzle_part == PART2):
        log(INFO, "******* Solution to part 2:")
        puzzleSolution2(fileLines)
        
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