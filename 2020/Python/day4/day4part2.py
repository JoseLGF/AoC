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

def stripPassportIntoFields(passportString):
    
    
    pass

def checkIfPassportIsValid(passportString):
    #print("Checking passport: " + passportString)
    # A passport is valid if it contains at least the following required fields:
    # byr (Birth Year)
    byr = re.search(r"byr:\d+", passportString)
    # iyr (Issue Year)
    iyr = re.search(r"iyr:\d+", passportString)
    # eyr (Expiration Year)
    eyr = re.search(r"eyr:\d+", passportString)
    # hgt (Height)
    hgt = re.search(r"hgt:\d+cm|hgt:\d+in", passportString)
    # hcl (Hair Color)
    hcl = re.search(r"hcl:#[A-Fa-f0-9]+", passportString)
    # ecl (Eye Color)
    ecl = re.search(r"ecl:[a-z]+", passportString)
    # pid (Passport ID)
    pid = re.search(r"pid:\d+", passportString)
    #
    # The Country ID is optional
    # cid (Country ID)
    cid = re.search(r"cid:\d+", passportString)
    
    isValid = True
    if (byr == None):
        #print ("byr not found.")
        isValid = False
    else:
        byr_number = re.search(r"\d+", byr.group())
        # Rules for byr:
        if ((not len(byr_number.group()) == 4) or int(byr_number.group()) > 2002 or int(byr_number.group()) < 1920):
            #print("byr invalid: " + str(int(byr_number.group())))
            isValid = False
    if (iyr == None):
        #print ("iyr not found.")
        isValid = False
    else:
        iyr_number = re.search(r"\d+", iyr.group())
        # Rules for iyr:
        if ((not len(iyr_number.group()) == 4) or int(iyr_number.group()) > 2020 or int(iyr_number.group()) < 2010):
            #print("iyr invalid: " + str(int(iyr_number.group())))
            isValid = False
    if (eyr == None):
        #print ("eyr not found.")
        isValid = False
    else:
        eyr_number = re.search(r"\d+", eyr.group())
        # Rules for eyr:
        if ((not len(eyr_number.group()) == 4) or int(eyr_number.group()) > 2030 or int(eyr_number.group()) < 2020):
            #print("eyr invalid: " + str(int(eyr_number.group())))
            isValid = False
    if (hgt == None):
        #print ("hgt not found.")
        isValid = False
    else:
        # Rules for hgt
        hgt_units  = re.search(r"cm|in", hgt.group())
        hgt_number = re.search(r"\d+", hgt.group())
        if (hgt_units.group() == "cm"):
            if (int(hgt_number.group()) < 150 or int(hgt_number.group()) > 193):
                #print("hgt: invalid height value for cm: " + str(int(hgt_number.group())))
                isValid = False
        if (hgt_units.group() == "in"):
            if (int(hgt_number.group()) < 59 or int(hgt_number.group()) > 76):
                #print("hgt: invalid height value for in: " + str(int(hgt_number.group())))
                isValid = False
    if (hcl == None):
        #print ("hcl not found or invalid.")
        isValid = False
    else:
        # extract color number
        hcl_str =  re.search(r"#[A-Fa-f0-9]+", hcl.group())
        if (not len(hcl_str.group()) == 7):
            #print("hcl: invalid number.")
            isValid = False
    if (ecl == None):
        #print ("ecl not found or invalid.")
        isValid = False
    else:
        # Rules for eye color
        ecl_code = re.sub(r"ecl:", "", ecl.group())
        ecl_code_filtered = re.search(r"amb|blu|brn|gry|grn|hzl|oth", ecl_code)
        if (ecl_code_filtered == None):
            #print("ecl: Invalid color code: " + ecl_code)
            isValid = False
    if (pid == None):
        #print ("pid not found.")
        isValid = False
    else:
        # 9 digits exactly, including leading zeroes
        pid_number = re.search(r"\d+", pid.group())
        if (not len(pid_number.group()) == 9):
            #print("pid: invalid number: " + pid_number.group())
            isValid = False
    if (cid == None):
        #print ("cid (optional) not found.")
        pass
    return isValid

def main():
    file = open('Input_day4.txt', 'r')
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

    print ("Day 4 Part 2 Solution: " + str(validPassports))
    
    
if __name__ == "__main__":
    main()