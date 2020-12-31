import re
import random

def extractFirstNumberInPasswordString(inputString):
    str_firstNumber = re.search(r"\d+", inputString)
    return(str_firstNumber.group())
    
def extractSecondNumberInPasswordString(inputString):
    str_secondNumberDirty = re.search(r"-\d+", inputString)
    str_secondNumber = re.sub(r"-", "", str_secondNumberDirty.group())
    return(str_secondNumber)
    
def extractCharacterOfRuleInPasswordString(inputString):
    str_characterOfRule = re.search(r"[a-z]", inputString)
    return(str_characterOfRule.group())
    
def extractPasswordFromPasswordString(inputString):
    str_passwordDirty = re.search(r": [a-z]+", inputString)
    str_password = re.sub(r": ", "", str_passwordDirty.group())
    return(str_password)
    

def checkIfPasswordIsValid(low, high, ruleChar, passwordString):
    # the low and high numbers now describe 1-indexed positions in the password string.
    # one and only one of the characters at those two positions must be the ruleChar.
    occurrences = 0
    if (passwordString[int(low)-1] == ruleChar):
        occurrences += 1
    if (passwordString[int(high)-1] == ruleChar):
        occurrences += 1
    
    if (occurrences == 1):
        return True
    
    return False


def main():
    file = open('Input_day2.txt', 'r')
    #file = open('sample_day2.txt', 'r')
    Lines = file.readlines()

    counter = 0
    for line in Lines:
        firstNumber  = extractFirstNumberInPasswordString(line)
        secondNumber = extractSecondNumberInPasswordString(line)
        ruleChar     = extractCharacterOfRuleInPasswordString(line)
        passString   = extractPasswordFromPasswordString(line)
        
        if (checkIfPasswordIsValid(firstNumber, secondNumber, ruleChar, passString)):
            #print("Valid   : " + line)
            counter += 1
        #else:
            #print("Invalid : " + line)
    print("Day 2 Part 2 Solution: " + str(counter))


if __name__ == "__main__":
    main()