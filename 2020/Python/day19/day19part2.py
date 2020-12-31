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
SampleInputFileName       = 'sample2.txt'
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
# Global config code ----------
if (RunLevel == SAMPLETESTING):
    numberOfRules = 6
if (RunLevel == FULLINPUTRUN):
    numberOfRules = 133
# -----------------------------
# Terminal rules are rules that will not be further expanded
if RunLevel == SAMPLETESTING:
    terminalRules = [4, 5]
    rule_a = 4
    rule_b = 5
if RunLevel == FULLINPUTRUN:
    terminalRules = [39, 45]
    rule_a = 45
    rule_b = 39

def puzzleSolution1(lines):

    log(SOLUTION, "day 19 Part 2: TODO")
    return

    log(INFO, "Rules:")
    rulesLines = getRules(lines)
    log(INFO, str(rulesLines))
    
    log(INFO, "Messages:")
    messages = getMessages(lines)
    log(INFO, str(messages))
    
    log(INFO, "Rules:")
    rules = []
    for ruleLine in rulesLines:
        rule = getRuleTokens(ruleLine)
        rules.append(rule)
    log(INFO, str(rules))
    
    log(INFO, "Expanding rule 0:")
    rulesList = [[8, 11]]
    log(INFO, "Running iterations:")
    
    finished = False
    # 35 - 2097152
    for i in range(36):
        rulesList = expandRuleList(rulesList, rules)
    #printRuleList(rulesList)
    log(DEBUG, "expanded " + str(len(rulesList)))
    
    log(INFO, "Converting expanded rules into strings:")
    strings = []
    for rule in rulesList:
        ruleString = ""
        for token in rule:
            if token == rule_a:
                ruleString += 'a'
            if token == rule_b:
                ruleString += 'b'
        strings.append(ruleString)
    #printRuleList(strings)
    
    log(INFO, "Checking matching messages...")
    matching_messages = 0
    for message in messages:
        if message in strings:
            matching_messages += 1
    log(INFO, str(matching_messages))

def printRuleList(ruleList):
    for rule in ruleList:
        print(rule)
    
def expandRuleList(ruleList, rules):
    #log(DEBUG, "Expanding " + str(ruleList))
    newRuleList = []
    for rule in ruleList:
        newRuleLeft  = []
        newRuleRight = []
        addBoth = False
        forkExpanded = False
        for token in rule:
            if ((token in terminalRules) or (forkExpanded)):
                # Case 0 - terminal rule, simply copy it to new rule
                newRuleLeft.append(token)
                newRuleRight.append(token)
            elif (type(token) == int):
                # Case 1 - not terminal rule; single value int
                # Substitute the definition of the rule as a list
                newRuleLeft.append(rules[token])
                newRuleRight.append(rules[token])
            elif (type(token) == list):
                # List expansion and substitution
                ruleToExpand = token
                if ('|' in ruleToExpand):
                    addBoth = True
                    leftPortion  = ruleToExpand[0:2]
                    rightPortion = ruleToExpand[3:5]
                    for leftToken in leftPortion:
                        newRuleLeft.append(leftToken)
                    for rightToken in rightPortion:
                        newRuleRight.append(rightToken)
                    forkExpanded = True
                else:
                    # No split, simply extract the rules from the list
                    for simpleToken in ruleToExpand:
                        newRuleRight.append(simpleToken)
                        newRuleLeft.append(simpleToken)
        newRuleList.append(newRuleLeft)
        if (addBoth):
            newRuleList.append(newRuleRight)
    return newRuleList

def expandRule(rule):
    # this function takes a single rule and returns a list of 
    # expanded rules
    
    return rule

def resolveRule(ruleTokens, rules):
    if (len(ruleTokens) == 1):
        token = ruleTokens[0]
        # Base case 1: One token is 'a' or 'b'
        if (token == 'a' or token == 'b'):
            log(DEBUG, "Base case 1: "+ str(ruleTokens[0]))
            return ruleTokens[0]
        # Recursive case 1: One token is another rule
        else:
            log(DEBUG, "Recursive case 1 for "+str(token))
            return resolveRule(rules[token], rules)
    else:
        # Recursive case 2: Two or more tokens, no '|'
        # TODO Modify!
        if (not '|' in ruleTokens):
            log(DEBUG, "Reducing with no tokens: " + str(ruleTokens))
            resolvedChars = ''
            for token in ruleTokens:
                resolvedToken = resolveRule([token], rules)
                log(DEBUG, "Recursive case 2 for "+str(token)+"::"+str(resolvedToken))
                for c in resolvedToken:
                    resolvedChars += c
                log(DEBUG, "Chars: " + resolvedChars)
                
            return resolvedChars
        # Recursive case 3: Several tokens, with '|'
        else:
            log(DEBUG, "Reducing with bifurcation: " + str(ruleTokens))
            listOfRules = []
            leftRule =  [ruleTokens[0], ruleTokens[1]]
            rightRule = [ruleTokens[3], ruleTokens[4]]
            log(DEBUG, "Reducing: " + str(leftRule))
            listOfRules.append(resolveRule(leftRule,rules))
            log(DEBUG, "Reducing: " + str(rightRule))
            listOfRules.append(resolveRule(rightRule,rules))
            return listOfRules
    
    

def getRuleTokens(testLine):
    ruleNumerRegex = r"[0-9]+: "
    ruleTokensStr = re.sub(ruleNumerRegex, "", testLine)
    log(DEBUG, ruleTokensStr)
    ruleTokens = ruleTokensStr.split(' ')
    parsedRulesTokens = []
    for ruleToken in ruleTokens:
        if (ruleToken == '"a"'):
            parsedRulesTokens.append('a')
        elif (ruleToken == '"b"'):
            parsedRulesTokens.append('b')
        elif (ruleToken == '|'):
            parsedRulesTokens.append('|')
        else:
            parsedRulesTokens.append(int(ruleToken))
    return parsedRulesTokens
    
    
def puzzleSolution2(lines):
    pass

def getRules(fileLines):
    return fileLines[0:numberOfRules]

def getMessages(fileLines):
    return fileLines[numberOfRules+1:]
    
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