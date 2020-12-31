def convertBoardingPassCodeToRowAndColumn(boardingPassString):
    #print("*******Calculating row and column for " + boardingPassString)
    
    # -------
    # Outputs
    # -------
    row = -1
    col = -1
    
    # ---------------
    # Row calculation
    # ---------------
    rowCodeLetters = boardingPassString[0:7]
    #print("Row code: " + rowCodeLetters)
    # Initialize row limits 0 to 127
    low = 0
    high = 127
    for letter in rowCodeLetters:
        # Taking the front half
        if (letter == 'F'):
            high = low + int((high - low) / 2)
        else: # back
            low = high - int((high - low) / 2)
        #print(letter + ": low = " + str(low) + ", high = " + str(high))
    row = high
    # ------------------
    # column calculation
    # ------------------
    columnCodeLetters = boardingPassString[7:10]
    #print("Col code: " + columnCodeLetters)
    # Initialize column limits 0 to 7
    low = 0
    high = 7
    for letter in columnCodeLetters:
        # Taking the Left (Lower) half
        if (letter == 'L'):
            high = low + int((high - low) / 2)
        else: # R (higher) half
            low = high - int((high - low) / 2)
        #print(letter + ": low = " + str(low) + ", high = " + str(high))
    col = high
    
    return [row, col]

def convertRowAndColumnToSeatID(row, col):
    return(row * 8 + col)

def boardingPassToSeatID(boardingPassString):
    rowAndCol = convertBoardingPassCodeToRowAndColumn(boardingPassString)
    seatID = convertRowAndColumnToSeatID(rowAndCol[0], rowAndCol[1])
    return seatID
    
def main():
    ProbeTesting  = 0
    RandomTesting = 1
    FullInputRun  = 2
    
    # ------------------------------------------
    # Configurations for the program and testing
    # ------------------------------------------
    RunLevel = FullInputRun
    FullInputFileName = 'Input_day5.txt'
    PrintInput = False
    SaveRunResults = False
    # ------------------------------------------
    
    
    # Probe testing
    if (RunLevel == ProbeTesting):
        #print(convertBoardingPassCodeToRowAndColumn("BFFFBBFRRR"))
        #print(convertBoardingPassCodeToRowAndColumn("FFFBBBFRRR"))
        #print(convertBoardingPassCodeToRowAndColumn("BBFFBBFRLL"))
        
        #print(boardingPassToSeatID("BFFFBBFRRR"))
        #print(boardingPassToSeatID("FFFBBBFRRR"))
        #print(boardingPassToSeatID("BBFFBBFRLL"))
        pass
    
    if (RunLevel == RandomTesting):
        #print("Selecting 5 boarding passes at random: ")
        RandomLines = []
        RandomLines.append(random.choice(Lines))
        RandomLines.append(random.choice(Lines))
        RandomLines.append(random.choice(Lines))
        RandomLines.append(random.choice(Lines))
        RandomLines.append(random.choice(Lines))
    
    # Full input run
    if (RunLevel == FullInputRun):
        #print("Running full input")
        #print("**Reading input file")
        # Open and read input file
        file = open(FullInputFileName, 'r')
        fileLines = file.readlines()
        
        if (PrintInput):
            for line in fileLines:
                #print(line, end='')
                pass
    
        #print("*******Read " + str(len(fileLines)) + " lines.")
        seatIDs = []
        for line in fileLines:
            seatID = boardingPassToSeatID(line)
            seatIDs.append(seatID)
        
        #print("*******Calculated seatIDs:")
        #print(seatIDs)
        #print("*******Maximum seat ID:")
        print("Day  5 Part 1: " + str(max(seatIDs)))
        
    
    
if __name__ == "__main__":
    main()