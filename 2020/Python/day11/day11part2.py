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
SampleInputFileName       = 'sample.txt'
PrintInput                = False
WriteRunResults           = True
resultsOutputFileName     = 'out_1.txt'
LogPrintLevel             = LOG_SOLUTION
LogWriteLevel             = LOG_DEBUG
GenerateRandomInputSample = False
RandomSampleSize          = 500
# -------------------------------------------------

# ----------------------------------------------------
# Functions and globals specific to the current puzzle
# ----------------------------------------------------
# directions, up, left, up-right, etc
#              X    Y
directions = [[0 ,  1],[0 , -1],[-1,  0],[1 ,  0],[-1,  1],[1 ,  1],[-1, -1],[1 , -1]]

def puzzleSolution(str_seats):    
    # remove EOL from lines
    seats = []
    for line in str_seats:
        seats.append(line.rstrip('\n'))
    
    height = len(seats)
    width  = len(seats[0])
    log(LOG_INFO, "******* Width: " + str(width))
    log(LOG_INFO, "******* height: " + str(height))
    
    iterations = 100000
    for iteration in range(iterations):
        nextIterationSeats = []
        for y in range(height):
            seatsRow = ""
            for x in range(width):
                #log(LOG_DEBUG, "calculate next " + str(x) + ", " + str(y))
                seatsRow += calculateNextSeatState(x, y, seats, width, height)
            nextIterationSeats.append(seatsRow)
        
        log(LOG_INFO, "******* Seats after iteration " + str(iteration))
        #printSeats(nextIterationSeats)
        
        changedSeats = getNumberOfChangedSeats(seats, nextIterationSeats, height, width)
        log(LOG_INFO, "******* Changed Seats: " + str(changedSeats))
        
        occupiedSeats = getOccupiedSeats(nextIterationSeats)
        
        
        if (changedSeats == 0):
            log(LOG_SOLUTION, "Day 11 Part 2 Solution: " + str(occupiedSeats))
            break
        
        seats = nextIterationSeats

def getOccupiedSeats(seats):
    count = 0
    for line in seats:
        for seat in line:
            if (seat == '#'):
                count += 1
    return count

def getNumberOfChangedSeats(oldSeats, newSeats, height, width):
    numberOfChangedSeats = 0
    for x in range(width):
        for y in range(height):
            if (not oldSeats[y][x] == newSeats[y][x]):
                numberOfChangedSeats += 1
    return numberOfChangedSeats

def printSeats(seats):
    for line in seats:
        print(line)

def calculateNextSeatState(seat_x, seat_y, seats, width, height):
    seatIsEmpty = (seats[seat_y][seat_x] == 'L')
    seatIsOccupied = (seats[seat_y][seat_x] == '#')
    adjacentSeats = getAdjacentSeats(seat_x, seat_y, width, height)
    
    occupiedVisibleSeats = 0
    for direction in directions:
        if (isASeatOccupiedAlongDirection(seat_x, seat_y, seats, width, height, direction)):
            occupiedVisibleSeats += 1
    
    # Otherwise, the seat's state does not change.
    seatNextState = seats[seat_y][seat_x]
    
    # If a seat is empty (L) and there are no occupied seats adjacent to it,
    # the seat becomes occupied.
    if (seatIsEmpty and occupiedVisibleSeats == 0):
        seatNextState = '#'
    
    # If a seat is occupied (#) and five or more seats adjacent to it are also occupied, 
    # the seat becomes empty.
    if (seatIsOccupied and occupiedVisibleSeats >= 5):
        seatNextState = 'L'
        
    return seatNextState

def isASeatOccupiedAlongDirection(seat_x, seat_y, seats, width, height, direction):
    direction_x = direction[0]
    direction_y = direction[1]
    far_index = 1
    far_seat_x = seat_x + far_index * direction_x
    far_seat_y = seat_y + far_index * direction_y
    while (far_seat_x < width and far_seat_x >= 0 and far_seat_y < height and far_seat_y >= 0):
        if (seats[far_seat_y][far_seat_x] == '#'):
            return True
        if (seats[far_seat_y][far_seat_x] == 'L'):
            return False
        # Recalculate far seats
        far_index += 1
        far_seat_x = seat_x + (far_index * direction_x)
        far_seat_y = seat_y + (far_index * direction_y)
    return False

def testGetAdjacentSeats(height, width):
    x = 0
    y = 0
    adjacentSeats = getAdjacentSeats(x, y, width, height)
    log(LOG_DEBUG, "Seats for 0,0: " + str(adjacentSeats))
    
    x = 5
    y = 5
    adjacentSeats = getAdjacentSeats(x, y, width, height)
    log(LOG_DEBUG, "Seats for 5, 5: " + str(adjacentSeats))
    
    x = 9
    y = 9
    adjacentSeats = getAdjacentSeats(x, y, width, height)
    log(LOG_DEBUG, "Seats for 5, 5: " + str(adjacentSeats))

def getAdjacentSeats(position_x, position_y, width, height):
    adjacentSeats = []
    for x in range(position_x-1, position_x+2):
        for y in range(position_y-1, position_y+2):
            #log(LOG_DEBUG, "checking " + str(x) + ", " + str(y))
            # out of bounds
            if (x < 0 or x > width-1 or y < 0 or y > height-1):
                continue
            # same square
            if (x == position_x and y == position_y):
                continue
            #log(LOG_DEBUG, "Adding " + str(x) + ", " + str(y))
            adjacentSeats.append([x, y])
    return adjacentSeats
    
def getNumberOfAdjacentOccupiedSeats(adjacentSeats, str_seats):
    count = 0
    for seat in adjacentSeats:
        x = seat[0]
        y = seat[1]
        if (str_seats[y][x] == '#'):
            log(LOG_DEBUG, "X: " + str(x) + ", y: " + str(y))
            count += 1
    return count

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