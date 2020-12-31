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
SOLUTION  = 5
# Puzzle partition
PART1     = 1
PART2     = 2

# -------------------------------------------------
# Global Configurations for the program and testing
# -------------------------------------------------
RunLevel                  = FULLINPUTRUN
puzzle_part               = PART1
FullInputFileName         = 'input.txt'
SampleInputFileName       = 'sample.txt'
PrintInput                = False
WriteRunResults           = False
RemoveEOLFromInputLines   = True
resultsOutputFileName     = 'out_1.txt'
LogPrintLevel             = SOLUTION
LogWriteLevel             = INFO
GenerateRandomInputSample = False
RandomSampleSize          = 500
# -------------------------------------------------

# ----------------------------------------------------
# Functions and globals specific to the current puzzle
# ----------------------------------------------------
UP    = 0
RIGHT = 1
DOWN  = 2
LEFT  = 3

def puzzleSolution1(lines):
    log(SOLUTION, "Day 20 Part 2: TODO")
    return
    """
    Calculated variables:
        - blocks           : All Blocks from the input. They include the Header and the content.
        - borders_count    : A dictionary that maps a border in a block and how many times that border is repeated in any other blocks.
        - cornerTilesIds   : A list that contains all found corner tiles. A corner tile is one which only has two shared borders with other blocks.
        - finalResultPart1 : The result of multiplying all four corner block IDs together.
        - unique_borders   : All borders that appear only once in all blocks' borders.
        - borders_dict     : A dictionary that maps the block IDs with their borders as integers.
    """
    
    tester(lines)
    
    blocks = getAllTileBlocks(lines)
    log(DEBUG, "Blocks:\n" + str(blocks))
    
    borders_count = {}
    for block in blocks:
        borders = getBordersFromTileBlock(block)
        for border in borders:
            borderInt = convertBorderToInt(border)
            if not borderInt in borders_count:
                borders_count[borderInt] = 1
            else:
                borders_count[borderInt] += 1
    log(INFO, "Borders count:\n" + str(borders_count))
    
    log(INFO, "Searching for corner tiles")
    cornerTilesIds = []
    for block in blocks:
        blockId = getIdFromTileBlock(block)
        blockBorders = getBordersFromTileBlock(block)
        count = 0
        #log(INFO, "ID : " + str(blockId))
        for border in blockBorders:
            border_int = convertBorderToInt(border)
            #log(INFO, str(border_int))
            count += borders_count[border_int]
        #log(INFO, "block ID: " + str(blockId)+" count " + str(count))
        if (count <= 6):
            cornerTilesIds.append(blockId)
            log(INFO, "Corner block ID: " + str(blockId))
            pass
    
    finalResultPart1 = 1
    for cornerTileId in cornerTilesIds:
        finalResultPart1 *= cornerTileId
    log(INFO, "Day 20 Part 1: " + str(finalResultPart1))
    
    log(INFO, "Number of tiles:" + str(len(blocks)))
    log(INFO, "Finding all borders which appear only once...")
    unique_borders = 0
    for key in borders_count:
        if borders_count[key] == 1:
            unique_borders += 1
    log(INFO, str(unique_borders))
    
    log(INFO, "Calculating borders dictionary...")
    borders_dict = {}
    for block in blocks:
        blockId = getIdFromTileBlock(block)
        blockBorders = getBordersFromTileBlock(block)
        blockBordersInts = []
        for border in blockBorders:
            border_int = convertBorderToInt(border)
            blockBordersInts.append(border_int)
            
        borders_dict[blockId] = blockBordersInts
    log(INFO, str(borders_dict))
        
    
    log(INFO, "Constructing simplified image array...")
    # simplified image is an array of IDs with their rotation
    simplified_image  = []
    image_side_length = int(math.sqrt(len(blocks)))
    for i in range(image_side_length):
        # Get x-y position in the array given the index
        x =     i % image_side_length
        y = math.floor(i / image_side_length)
        log(INFO, "x, y = " + str(x) + "," + str(y))
        blockId = -1
        # Find next block
        if (x == 0 and y == 0):
            # Initial top-left block
            blockId = cornerTilesIds[0]
            log(INFO, "Choosing block ID: " + str(blockId))
        elif (y == 0):
            # Top row
            # Find next block by looking at previous block
            leftBlockId = simplified_image[i-1]
            
        
        # Get the block borders
        blockBorders = borders_dict[blockId]
        
        # Correct block rotation
        if (x == 0 and y == 0):
            # Initial top-left block
            rotation = 0
            isRotationCorrect = False
            while not isRotationCorrect:
                blockBorders    = rotateBorders(blockBorders)
                rotation += 1
                upBorderCount   = borders_count[blockBorders[UP]]
                leftBorderCount = borders_count[blockBorders[LEFT]]
                if (upBorderCount == 1 and leftBorderCount == 1):
                    isRotationCorrect = True
            rotation = rotation % 4
            log(INFO, "Correct block rotation: " + str(rotation))
        
        # Append block to image
        simplified_image.append([blockId, rotation])
        log(INFO, "Image: " + str(simplified_image))
    """
    # Add the first element, a corner block
    simplified_image.append([1951,-1])
    log(INFO, str(simplified_image))
    # Correct image rotation
    simplified_image_index = 0
    if (simplified_image_index == 0):
        # top-left corner
        # Verify that the left and up borders are correct
        isCorrect = False
        while (not isCorrect):
            rotatedBorders = getBlockIdsRotatedBorders(Id, rotation, borders)
            # Calculate Borders
            up =
            right =
            down =
            left =
        pass
    """

def rotateBorders(tileBorders):
    newBorders = []
    newBorders.append(tileBorders[3])
    newBorders.append(tileBorders[0])
    newBorders.append(tileBorders[1])
    newBorders.append(tileBorders[2])
    return newBorders


def puzzleSolution2(lines):
    pass

def tester(lines):
    tile = ["Tile 2729:",
            ".....#####",
            "##..##.#.#",
            "......#.##",
            "#....#.#.#",
            "#......##.",
            "#...#..#.#",
            "#.........",
            ".......##.",
            "#.#..#....",
            "#.#.###..#"]
    
    
    tileID = getIdFromTileBlock(tile)
    log(DEBUG, "Tile ID:" + str(tileID))
    
    borders = getBordersFromTileBlock(tile)
    log(DEBUG, "Borders:" + str(borders))
    
    for border in borders:
        border_int = convertBorderToInt(border)
        log(DEBUG, "Border:" + str(border)+":"+str(border_int))
    
    log(INFO, "Verifying Block borders rotation function...")
    
    
    pass

def getIdFromTileBlock(tileBlock):
    # TileBlock: List of strings
    tileHeader = tileBlock[0]
    tileID = tileHeader[5:9]
    return int(tileID)

def getTileContent(tileBlock):
    # TileBlock: List of strings
    return tileBlock[1:]

def getBordersFromTileBlock(tileBlock):
    # TileBlock: List of strings including the header
    tileContent = getTileContent(tileBlock)
    upBorder    = tileContent[0]
    downBorder  = tileContent[9]
    leftBorder  = ''
    rightBorder = ''
    
    for i in range(10):
        line = tileContent[i]
        leftBorder  += line[0]
        rightBorder += line[9]
    return [upBorder, rightBorder, downBorder, leftBorder]

def convertBorderToInt(border):
    # border: string of length 10
    
    result_1 = 0
    index = 0
    for bit in border:
        if bit == '#':
            result_1 += 2**index
        index += 1
    
    border = border[::-1]
    
    result_2 = 0
    index = 0
    for bit in border:
        if bit == '#':
            result_2 += 2**index
        index += 1
        
    return min(result_1,result_2)

def getAllTileBlocks(lines):
    # lines: list of strings specifying several blocks
    blockLength = 12
    nextBlock = 0
    blocks = []
    while nextBlock < len(lines):
        blocks.append(lines[nextBlock:nextBlock+blockLength-1])
        nextBlock += blockLength
    return blocks

def printBlockIdsAndBorders(blocks):  
    # print IDs and their borders
    for block in blocks:
        blockId = getIdFromTileBlock(block)
        borders = getBordersFromTileBlock(block)
        borders_ints = []
        for border in borders:
            borders_ints.append(convertBorderToInt(border))
        log(INFO, "ID: " + str(blockId) + " Borders: " + str(borders_ints))


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