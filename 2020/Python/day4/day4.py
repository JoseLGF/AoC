import re
import random

def separateLinesIntoPassports(lines):
    passports = []
    
    currentPassport = ""
    for line in lines:
        if (not len(line) == 1):
            currentPassport += line
        else:
            passports.append(currentPassport)
            currentPassport = ""
    # Add the last passport (Had EOL instead of newline)
    passports.append(currentPassport)
    #print("** Found " + str(len(passports)) + " passports.")
    return passports

def checkIfPassportIsValid(passportString):
    #print("Checking passport: " + passportString)
    # A passport is valid if it contains at least the following required fields:
    # byr (Birth Year)
    byr = re.search(r"byr:", passportString)
    # iyr (Issue Year)
    iyr = re.search(r"iyr:", passportString)
    # eyr (Expiration Year)
    eyr = re.search(r"eyr:", passportString)
    # hgt (Height)
    hgt = re.search(r"hgt:", passportString)
    # hcl (Hair Color)
    hcl = re.search(r"hcl:", passportString)
    # ecl (Eye Color)
    ecl = re.search(r"ecl:", passportString)
    # pid (Passport ID)
    pid = re.search(r"pid:", passportString)
    #
    # The Country ID is optional
    # cid (Country ID)
    cid = re.search(r"cid:", passportString)
    
    isValid = True
    if (byr == None):
        #print ("byr not found.")
        isValid = False
    if (iyr == None):
        #print ("iyr not found.")
        isValid = False
    if (eyr == None):
        #print ("eyr not found.")
        isValid = False
    if (hgt == None):
        #print ("hgt not found.")
        isValid = False
    if (hcl == None):
        #print ("hcl not found or invalid.")
        isValid = False
    if (ecl == None):
        #print ("ecl not found or invalid.")
        isValid = False
    if (pid == None):
        #print ("pid not found.")
        isValid = False
    if (cid == None):
        #print ("cid (optional) not found.")
        pass
    return isValid

def main():
    file = open('input_day4.txt', 'r')
    #file = open('sample_day4.txt', 'r')
    fileLines = file.readlines()
    
    batchPassports = []
    
    for line in fileLines:
        batchPassports.append(line)

    # return a list with parsed passports
    passports = separateLinesIntoPassports(batchPassports)
    
    # check Validity of all passports
    validPassports = 0
    for passport in passports:
        if (checkIfPassportIsValid(passport)):
            validPassports += 1

    print ("Day  4 Part 1: " + str(validPassports))
    
    
if __name__ == "__main__":
    main()