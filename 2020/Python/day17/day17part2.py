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
WriteRunResults           = True
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
# He who controls the cubes, controls the world.
class CubeManager:
    
    numberOfCycles = None
    initial_height = None
    initial_width  = None
    total_height   = None
    total_width    = None
    layer_size     = None
    total_layers   = None
    totalCubeSize  = None
    hypercubeSize  = None
    cube           = None
    simulationStep = 0
    
    def __init__(self, initial_height, initial_width, numberOfCycles):
        self.numberOfCycles = numberOfCycles
        self.initial_height = initial_height
        self.initial_width  = initial_width
        self.total_height   = self.initial_height + 2*self.numberOfCycles
        self.total_width    = self.initial_width  + 2*self.numberOfCycles
        self.layer_size     = self.total_height*self.total_width
        self.total_layers   = 1 + 2*self.numberOfCycles
        self.totalCubeSize  = (self.total_width)*(self.total_height)*(self.total_layers)
        self.totalCubes     = 1 + 2*self.numberOfCycles
        self.hypercubeSize  = self.totalCubes * self.totalCubeSize
        self.cube = [0 for i in range(self.hypercubeSize)]
    
    def AbsoluteXyzwToIndex(self, x, y, z, w):
        return w*self.totalCubeSize + (z*self.layer_size + y*self.total_width + x)
    
    def populateInitialActiveSurface(self, lines):
        zcoord = self.numberOfCycles
        wcoord = self.numberOfCycles
        for lineIndex in range(len(lines)):
            line = lines[lineIndex]
            ycoord = lineIndex + self.numberOfCycles
            for charIndex in range(len(line)):
                bit = line[charIndex]
                xcoord = charIndex + self.numberOfCycles
                if (bit == '#'):
                    # bit is on
                    cubeId = self.AbsoluteXyzwToIndex(xcoord, ycoord, zcoord, wcoord)
                    self.cube[cubeId] = 1
    
    def getCrossSectionInAbsCoord(self, abs_z, abs_w):
        crossSectionLine = ""
        initialChar = abs_w*self.totalCubeSize + abs_z*self.layer_size
        for charIndex in range(initialChar, initialChar+self.layer_size):
            if (charIndex % self.total_width == 0):
                crossSectionLine += '\n'
            if self.cube[charIndex] == 1:
                crossSectionLine += '#'
            else:
                crossSectionLine += '.'
        return crossSectionLine
        
    def getNeighborsInAbsCoord(self, x, y, z, w):
        positions = []
        for xi in range(x-1,x+2):
            if (xi < 0 or xi >= self.total_width):
                continue
            for yi in range(y-1,y+2):
                if (yi < 0 or yi >= self.total_height):
                    continue
                for zi in range(z-1,z+2):
                    if (zi < 0 or zi >= self.total_layers):
                        continue
                    for wi in range(w-1,w+2):
                        if (wi < 0 or wi >= self.totalCubes):
                            continue
                        if (xi == x and yi == y and zi == z and wi == w):
                            continue
                        else:
                            # Neighbor point is within range, add it to the cube
                            neighborId = self.AbsoluteXyzwToIndex(xi, yi, zi, wi)
                            positions.append(neighborId)
        log(PROFILING, "Neighbors(" + str(len(positions)) + "): " + str(positions))
        return positions
        
    def getActiveNeighborsInAbsCoords(self, x, y, z, w):
        neighbors = self.getNeighborsInAbsCoord(x, y, z, w)
        count = 0
        for neighbor in neighbors:
            log(DEBUG, "Indexing " + str(neighbor))
            if (self.cube[neighbor] == 1):
                count += 1
        return count
        
    def indexToAbsCoords(self, index):
        cubeIndex   = index % self.totalCubeSize
        layerIndex  = cubeIndex % self.layer_size
        w           = math.floor(index      / self.totalCubeSize)
        z           = math.floor(cubeIndex      / self.layer_size)
        y           = math.floor(layerIndex / self.total_width)
        x           = layerIndex % self.total_width
        return [x, y ,z, w]
        
    def runSimulationStep(self):
        nextCube = []
        for cubeIndex in range(len(self.cube)):
            cubeBit = self.cube[cubeIndex]
            [x, y, z, w] = self.indexToAbsCoords(cubeIndex)
            xyzw = [x, y, z, w]
            log(PROFILING, "Index:" + str(cubeIndex) +" : xyzw=" + str(xyzw)+"act: " + str(cubeBit))
            cubeBitActiveNeighbors = self.getActiveNeighborsInAbsCoords(x, y, z, w)
            log(PROFILING, "Active:" + str(cubeBitActiveNeighbors))
            
           
            if (cubeBit == 1):
                if (cubeBitActiveNeighbors == 2):
                    # Cube remains active
                    nextCube.append(1)
                elif (cubeBitActiveNeighbors == 3):
                    # Cube remains active
                    nextCube.append(1)
                else:
                    # Cube becomes inactive
                    log(PROFILING, "Deactivate " + str(xyzw) + "Neighbors:" + str(cubeBitActiveNeighbors))
                    nextCube.append(0)
            else:
                if (cubeBitActiveNeighbors == 3):
                    log(PROFILING, "Activate " + str(xyzw) + ": 3 active neighbors" + str(cubeBitActiveNeighbors))
                    nextCube.append(1)
                else:
                    nextCube.append(0)
                    
        self.cube = nextCube
        
    def getActiveBits(self):
        return self.cube.count(1)
    
    def selfTest(self):
        for i in range(len(self.cube)):
            # convert i to absolute coordinates and back!
            [x, y, z, w] = self.indexToAbsCoords(i)
            back_i = self.AbsoluteXyzwToIndex(x, y, z, w)
            if (not i == back_i):
                log(ERROR, "Error, wrong conversion happened!")
                log(ERROR, str(i) + "->" + str([x, y, z, w]) + "->" + str(back_i))
    
def puzzleSolution1(lines):
    numberOfCycles = 6
    initial_height = len(lines)
    initial_width  = len(lines[0])

    Cube = CubeManager(initial_height, initial_width, numberOfCycles)
    log(INFO, "Total Cube size: " + str(Cube.totalCubeSize))
    
    log(INFO, "Running self test...")
    Cube.selfTest()
    log(INFO, "Self test passed")
   
    log(INFO, "Populating initial cube surface... ")
    Cube.populateInitialActiveSurface(lines)
   
    log(INFO, "Cross section at z= 0")
    crossSection0 = Cube.getCrossSectionInAbsCoord(6, 6)
    log(INFO, str(crossSection0))
   
    log(INFO, "Neighbors of 6,6,6:")
    neighbors = Cube.getNeighborsInAbsCoord(6, 6, 6, 6)
    log(INFO, str(neighbors))
   
    log(INFO, "Active neighbors of 6,6,6:")
    activeNeighbors = Cube.getActiveNeighborsInAbsCoords(6,6,6,6)
    log(INFO, str(activeNeighbors))
   
    
    # Start cycles simulation
    log(INFO, "******* Simulating cycles")
    
    for cycle in range(numberOfCycles):
        Cube.runSimulationStep()
   
    # count active cubes after 6 iterations
    log(INFO, "Active neighbors at the end")
    finalActiveNeighbors = Cube.getActiveBits()
    log(SOLUTION, "Day 17 Part 2:" + str(finalActiveNeighbors))

def puzzleSolution2(lines):
    pass

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