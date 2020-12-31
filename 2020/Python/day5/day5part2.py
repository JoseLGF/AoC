# Run types
PROBETESTING  = 0
RANDOMTESTING = 1
FULLINPUTRUN  = 2
# Log levels
LOG_DEBUG     = 0
LOG_PROFILING = 1
LOG_INFO      = 2
LOG_WARNING   = 3
LOG_ERROR     = 4
LOG_SOLUTION  = 5

# ------------------------------------------
# Global Configurations for the program and testing
# ------------------------------------------
RunLevel = FULLINPUTRUN
FullInputFileName = 'Input_day5.txt'
PrintInput = False
WriteRunResults = True
resultsOutputFileName = "out_1.txt"
LogPrintLevel = LOG_SOLUTION
LogWriteLevel = LOG_DEBUG
RandomSampleSize = 5
# ------------------------------------------

# ------------------
# Global definitions
# ------------------
logStr = ""

def convertBoardingPassCodeToRowAndColumn(boardingPassString):
    log(LOG_PROFILING, "*******Calculating row and column for " + boardingPassString)
    
    # -------
    # Outputs
    # -------
    row = -1
    col = -1
    
    # ---------------
    # Row calculation
    # ---------------
    rowCodeLetters = boardingPassString[0:7]
    log(LOG_DEBUG, "Row code: " + rowCodeLetters)
    # Initialize row limits 0 to 127
    low = 0
    high = 127
    for letter in rowCodeLetters:
        # Taking the front half
        if (letter == 'F'):
            high = low + int((high - low) / 2)
        else: # back
            low = high - int((high - low) / 2)
        log(LOG_DEBUG, letter + ": low = " + str(low) + ", high = " + str(high))
    row = high
    # ------------------
    # column calculation
    # ------------------
    columnCodeLetters = boardingPassString[7:10]
    log(LOG_DEBUG, "Col code: " + columnCodeLetters)
    # Initialize column limits 0 to 7
    low = 0
    high = 7
    for letter in columnCodeLetters:
        # Taking the Left (Lower) half
        if (letter == 'L'):
            high = low + int((high - low) / 2)
        else: # R (higher) half
            low = high - int((high - low) / 2)
        log(LOG_DEBUG, letter + ": low = " + str(low) + ", high = " + str(high))
    col = high
    
    return [row, col]

def convertRowAndColumnToSeatID(row, col):
    return(row * 8 + col)

def boardingPassToSeatID(boardingPassString):
    rowAndCol = convertBoardingPassCodeToRowAndColumn(boardingPassString)
    seatID = convertRowAndColumnToSeatID(rowAndCol[0], rowAndCol[1])
    return seatID
 
def main():

    # Probe testing
    if (RunLevel == PROBETESTING):
        print(convertBoardingPassCodeToRowAndColumn("BFFFBBFRRR")) # Good!
        print(convertBoardingPassCodeToRowAndColumn("FFFBBBFRRR")) # Good!
        print(convertBoardingPassCodeToRowAndColumn("BBFFBBFRLL")) # Good!
        
        print(boardingPassToSeatID("BFFFBBFRRR"))
        print(boardingPassToSeatID("FFFBBBFRRR"))
        print(boardingPassToSeatID("BBFFBBFRLL"))
    
    # Random Testing
    if (RunLevel == RANDOMTESTING):
        print("Selecting " + str(RandomSampleSize) + " boarding passes at random: ")
        RandomLines = []
        for i in range(RandomSampleSize):
            RandomLines.append(random.choice(Lines))
    
    # Full input run
    if (RunLevel == FULLINPUTRUN):
        log(LOG_INFO, "*******Running full input")
        log(LOG_INFO, "*******Reading input file")
        # Open and read input file
        file = open(FullInputFileName, 'r')
        fileLines = file.readlines()
        
        if (PrintInput):
            for line in fileLines:
                print(line, end='')
        log(LOG_INFO, "*******Read " + str(len(fileLines)) + " lines.")
        
        log(LOG_INFO, "*******Calculating seatIDs...")
        seatIDs = []
        for line in fileLines:
            seatID = boardingPassToSeatID(line)
            seatIDs.append(seatID)
        
        log(LOG_DEBUG, str(seatIDs))
        log(LOG_INFO, "*******Maximum seat ID:")
        log(LOG_INFO, str(max(seatIDs)))
        
        # Find the missing seat between min (45) and max (816)
        missingSeats = []
        for seat in range(45,817):
            log(LOG_DEBUG, "Searching seat: " + str(seat))
            if not seat in seatIDs:
                missingSeats.append(seat)
        log(LOG_SOLUTION, "Day 5 Part 2 Solution: " + str(missingSeats[0]))
        
        
        if (WriteRunResults):
            writeRunResults(seatIDs)
            
# Implement this function to write specific results to a text file
def writeRunResults(seatIDs):            
    log(LOG_INFO, "*******Writing results to specified output file")
    s = ""
    for id in seatIDs:
        s += str(id) + "\n"
        
    with open(resultsOutputFileName, "w") as file: 
        # Writing data to a file 
        file.write(s)
        

def log(type, message):
    global logStr
    
    if (not type < LogPrintLevel):
        print(message)
    
    if (not type < LogWriteLevel):
        logStr += message + "\n"

def writeLogFile():
    global logStr
    with open("run_logfile.txt", "w") as file: 
        # Writing data to a file 
        file.write(logStr)

if __name__ == "__main__":
    main()
    writeLogFile()
    