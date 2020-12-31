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
RunLevel = FULLINPUTRUN
FullInputFileName = 'input_day6.txt'
SampleInputFileName = 'sample_day6.txt'
PrintInput = False
WriteRunResults = True
resultsOutputFileName = "out_1.txt"
LogPrintLevel = LOG_SOLUTION
LogWriteLevel = LOG_DEBUG
RandomSampleSize = 1
# ------------------------------------------

# ------------------
# Global definitions
# ------------------
logStr = ""


def separateLinesIntoGroups(lines):
    groups = []
    
    currentGroup = []
    for line in lines:
        if (not len(line.rstrip('\n')) == 0):
            currentGroup.append(line.rstrip('\n'))
        else:
            groups.append(currentGroup)
            currentGroup = []
    # Add the last group (Had EOL instead of newline)
    groups.append(currentGroup)
    log(LOG_INFO, "******* Found " + str(len(groups)) + " groups.")
    return groups

def commonElementsinGroup(group):
    # group is a list of lists
    
    # Add all elements of the first line to the commons
    presumed_commons = group[0]
    commons = []
    
    # if a character from the presumed_commons is not on the line,
    # Do not add it to the commons
    for character in presumed_commons:
        isCharacterInCommons = True
        for line in group:
                if not character in line:
                    isCharacterInCommons = False
        
        if (isCharacterInCommons):
            commons.append(character)
    
    return commons
        

def main():

    # Probe testing
    if (RunLevel == PROBETESTING):
        log(LOG_INFO, "******* Running Probe Testing")
    
    # Random Testing
    if (RunLevel == RANDOMTESTING):
        print("Selecting " + str(RandomSampleSize) + " boarding passes at random: ")
        RandomLines = []
        for i in range(RandomSampleSize):
            RandomLines.append(random.choice(Lines))
    
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
        log(LOG_INFO, "******* Read " + str(len(fileLines)) + " lines.")
        
        log(LOG_INFO, "******* Separating strings into groups.")
        groups = separateLinesIntoGroups(fileLines)
        log(LOG_INFO, str(groups))
        
        log(LOG_INFO, "******* Finding common elements in each group")
        commons = []
        for group in groups:
            commons_in_group = commonElementsinGroup(group)
            commons.append(commons_in_group)
            log(LOG_DEBUG, str(commons_in_group) + " = " + str(len(commons_in_group)))
            
        log(LOG_INFO, "******* Counting common elements in all groups")
        count = 0
        for each in commons:
            count += len(each)
        log(LOG_SOLUTION, "Day  6 Part 2 (Sample) Solution: " + str(count))
    
    
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
        
        log(LOG_INFO, "******* Separating strings into groups.")
        groups = separateLinesIntoGroups(fileLines)
        log(LOG_INFO, str(groups))
        
        log(LOG_INFO, "******* Finding common elements in each group")
        commons = []
        for group in groups:
            commons_in_group = commonElementsinGroup(group)
            log(LOG_DEBUG, str(commons_in_group))
            commons.append(commons_in_group)
            log(LOG_DEBUG, str(commons_in_group) + " = " + str(len(commons_in_group)))
            
            
        log(LOG_INFO, "******* Counting common elements in all groups")
        count = 0
        for each in commons:
            count += len(each)
        log(LOG_SOLUTION, "Day  6 Part 2: " + str(count))
            
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
    