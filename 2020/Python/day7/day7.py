import random

# Run types
PROBETESTING  = 0
SAMPLETESTING = 1
RANDOMTESTING = 2
FULLINPUTRUN  = 3
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
RunLevel              = FULLINPUTRUN
FullInputFileName     = 'input_day7.txt'
SampleInputFileName   = 'sample_day7.txt'
PrintInput            = False
WriteRunResults       = True
resultsOutputFileName = "out_1.txt"
LogPrintLevel         = LOG_SOLUTION
LogWriteLevel         = LOG_INFO
RandomSampleSize      = 500
# ------------------------------------------

# ------------------
# Global definitions
# ------------------
logStr = ""

def separateRuleIntoColorsAndBags(ruleStr):
    # split by space
    ruleTokens = ruleStr.split(sep=' ')
    log(LOG_DEBUG, str(ruleTokens))
    
    containerBagInRule = ruleTokens[0]+ruleTokens[1]
    log(LOG_DEBUG, containerBagInRule)
    
    containedBagsInRule = []
    # When no bags are contained in the rule, the word "no"
    # appears at position 4 (zero indexed)
    if (not ruleTokens[4] == "no"):
        # parse remaining tokens
        containedBagFirstColor = ""
        for token_index in range(len(ruleTokens)):
            if token_index > 4:
                if (token_index % 4 == 0):
                    # number of contained bags
                    pass
                if (token_index % 4 == 1):
                    containedBagFirstColor = ruleTokens[token_index]
                if (token_index % 4 == 2):
                    containedBagsInRule.append(containedBagFirstColor + ruleTokens[token_index])
                if (token_index % 4 == 0):
                    # this is the word "bag." or "bags."
                    pass
    #log(LOG_DEBUG, containerBagInRule + "->" + str(containedBagsInRule))
    log(LOG_DEBUG, str({containerBagInRule: containedBagsInRule}))
    return {containerBagInRule: containedBagsInRule}

# Required for recursive search
foundContainers = []
def searchBagRecursively(searchBagColor, rulesDict):
    log(LOG_PROFILING, "-Searching bag of color " + searchBagColor)
    for containerBagColor in rulesDict:
        log(LOG_DEBUG, "Searching in " + containerBagColor)
        for containedBag in rulesDict[containerBagColor]:
            log(LOG_DEBUG, "Found " + containedBag)
            if (containedBag == searchBagColor):
                # Do not add duplicates
                if (not containerBagColor in foundContainers):
                    foundContainers.append(containerBagColor)
                    searchBagRecursively(containerBagColor, rulesDict)
    


def main():

    # Probe testing
    if (RunLevel == PROBETESTING):
        log(LOG_INFO, "******* Running Probe Testing")
    
    # Random Testing
    if (RunLevel == RANDOMTESTING):
        log(LOG_INFO, "******* Selecting " + str(RandomSampleSize) + " rules at random: ")
        
        file = open(FullInputFileName, 'r')
        fileLines = file.readlines()
        
        RandomLines = []
        for i in range(RandomSampleSize):
            RandomLines.append(random.choice(fileLines))
    
        if (PrintInput):
            log(LOG_INFO, "******* Raw input random rules:")
            for line in RandomLines:
                print(line, end='')
        print()
        log(LOG_INFO, "******* Read " + str(len(fileLines)) + " lines.")
        
        log(LOG_INFO, "******* Parsing rules...")
        rulesDict = {}
        for rule in RandomLines:
            rulesDict.update(separateRuleIntoColorsAndBags(rule))
        log(LOG_DEBUG, str(rulesDict))
            
        log(LOG_INFO, "******* Searching container bags for color shinygold")
        searchBagRecursively("shinygold", rulesDict)
        # After recursive search is done, check contained bags
        log(LOG_INFO, "******* Contained bags: ")
        log(LOG_INFO, str(foundContainers))
        log(LOG_INFO, "******* Solution: ")
        log(LOG_INFO, str(len(foundContainers)))
    
    # Sample Testing
    if (RunLevel == SAMPLETESTING):
        print("Running with the sample provided as input.")
        
        # Open and read input file
        file = open(SampleInputFileName, 'r')
        fileLines = file.readlines()
        
        if (PrintInput):
            log(LOG_INFO, "******* Raw input:")
            for line in fileLines:
                print(line, end='')
        print()
        log(LOG_INFO, "******* Read " + str(len(fileLines)) + " lines.")
        
        log(LOG_INFO, "******* Parsing rules...")
        rulesDict = {}
        for rule in fileLines:
            rulesDict.update(separateRuleIntoColorsAndBags(rule))
        log(LOG_DEBUG, str(rulesDict))
            
        log(LOG_INFO, "******* Searching container bags for color shinygold")
        searchBagRecursively("shinygold", rulesDict)
        # After recursive search is done, check contained bags
        log(LOG_INFO, "******* Contained bags: ")
        log(LOG_INFO, str(foundContainers))
        log(LOG_INFO, "******* Solution: ")
        log(LOG_INFO, str(len(foundContainers)))
        
    
    
    # Full input run
    if (RunLevel == FULLINPUTRUN):
        log(LOG_INFO, "******* Running full input")
        
        # Open and read input file
        file = open(FullInputFileName, 'r')
        fileLines = file.readlines()
        
        if (PrintInput):
            log(LOG_INFO, "******* Raw input:")
            for line in fileLines:
                print(line, end='')
        log(LOG_INFO, "******* Read " + str(len(fileLines)) + " lines.")
        
        log(LOG_INFO, "******* Parsing rules...")
        rulesDict = {}
        for rule in fileLines:
            rulesDict.update(separateRuleIntoColorsAndBags(rule))
        log(LOG_DEBUG, str(rulesDict))
            
        log(LOG_INFO, "******* Searching container bags for color shinygold")
        searchBagRecursively("shinygold", rulesDict)
        # After recursive search is done, check contained bags
        log(LOG_INFO, "******* Contained bags: ")
        log(LOG_INFO, str(foundContainers))
        log(LOG_SOLUTION, "Day 7 Part 1 Solution: "+ str(len(foundContainers)))
            
# Implement this function to write specific results to a text file
def writeRunResults(seatIDs):            
    log(LOG_INFO, "******* Writing results to specified output file")
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
    log(LOG_INFO, "******* Writing results to run_logfile.txt.")
    with open("run_logfile.txt", "w") as file: 
        # Writing data to a file 
        file.write(logStr)

if __name__ == "__main__":
    main()
    writeLogFile()
    