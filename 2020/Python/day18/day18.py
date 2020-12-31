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
puzzle_part               = PART1
FullInputFileName         = 'input.txt'
SampleInputFileName       = 'sample.txt'
PrintInput                = True
WriteRunResults           = True
RemoveEOLFromInputLines   = True
resultsOutputFileName     = 'out_1.txt'
LogPrintLevel             = INFO
LogWriteLevel             = DEBUG
GenerateRandomInputSample = False
RandomSampleSize          = 500
# -------------------------------------------------

# ----------------------------------------------------
# Functions and globals specific to the current puzzle
# ----------------------------------------------------
def puzzleSolution1(lines):
    # Testing functions
    log(INFO, "Test 0: Expect 2")
    t0 = evaluate('2')
    log(INFO, str(t0))
    
    log(INFO, "Test 1: Expect 3")
    t1 = evaluate('1 + 2')
    log(INFO, str(t1))
    
    log(INFO, "Test 2: Expect 71")
    t1 = evaluate('1 + 2 * 3 + 4 * 5 + 6')
    log(INFO, str(t1))
    
    log(INFO, "Test 3: Expect 26")
    t1 = evaluate('2 * 3 + (4 * 5)')
    log(INFO, "Final solution: " + str(t1))
    
    log(INFO, "Test 3: Expect 437")
    t1 = evaluate('5 + (8 * 3 + 9 + 3 * 4 * 3)')
    log(INFO, "Final solution: " + str(t1))
    
    log(INFO, "Test 4: Expect 12240")
    t1 = evaluate('5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))')
    log(INFO, "Final solution: " + str(t1))
    
    linesSum = 0
    for line in lines:
        linesSum += evaluate(line)
    log(INFO, "Lines sum: " + str(linesSum))
    

def puzzleSolution2(lines):
    pass

def evaluate(expression):
    if ('(' in expression):
        return evaluate(reduceParentheses(expression))
    # else (No parentheses)
    tokens = expression.split(' ')
    log(DEBUG, "tokens")
    log(DEBUG, str(tokens))
    return evaluateTokens(tokens)

def reduceParentheses(expression_string):
    log(DEBUG, "Reducing parenthesis in " + expression_string)
    parenth_counter         = 0
    reducedExpressionString = ""
    openParenthIndex        = None
    closeParenthIndex       = None
    expressionToReduce      = ""
    for symbol_index in range(len(expression_string)):
        symbol = expression_string[symbol_index]
        if (symbol == '('):
            parenth_counter += 1
            if (parenth_counter == 1):
                # This is the first opening parenthesis
                openParenthIndex = symbol_index
        elif (symbol == ')'):
            parenth_counter -= 1
            if (parenth_counter == 0):
                # This is the closing parenthesis of the first opening
                closeParenthIndex = symbol_index
                # Recursive case:
                log(DEBUG, "Evaluating : " + expression_string[openParenthIndex+1:closeParenthIndex])
                reducedResult = evaluate(expression_string[openParenthIndex+1:closeParenthIndex])
                log(DEBUG, str(reducedResult))
                return (expression_string[0:openParenthIndex]+str(reducedResult)+expression_string[closeParenthIndex+1:])
        
        
    pass
    
def evaluateTokens(tokens):
    log(DEBUG, "call to evalTokens: " + str(tokens))
    # Base case 1: Only 1 token (assume it is a number)
    if (len(tokens) == 1):
        return int(tokens[0])
    else:
        # Multiple tokens with no parentheses
        if (not '(' in tokens):
            leftOperand   = int(tokens[0])
            operator      = tokens[1]
            rightOperand  = int(tokens[2])
            
            if (operator == '+'):
                log(DEBUG, "result: " +str(leftOperand)+" + "+str(rightOperand))
                result = leftOperand + rightOperand
            if (operator == '-'):
                log(DEBUG, str(leftOperand) +" - "+str(rightOperand))
                result = leftOperand - rightOperand
            if (operator == '*'):
                log(DEBUG, str(leftOperand) +" * "+str(rightOperand))
                result = leftOperand * rightOperand
            # Base case 2: Only two operands
            if (len(tokens) == 3):
                return result
            # Recursive case 1: More than two operands
            if (len(tokens) > 3):
                remainder = tokens[3:]
                remainder.insert(0, result)
                log(DEBUG, "Recursion with :" + str(remainder))
                return evaluateTokens(remainder)
        log(ERROR, "ERROR: Evaluating tokens with parentheses")

    

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