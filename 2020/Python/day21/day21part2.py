# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import random
import math
import re
from itertools import permutations

# Run levels
PROBETESTING  = 0
SAMPLETESTING = 1
FULLINPUTRUN  = 2

# Log Levels
DEBUG     = 0
PROFILING = 1
INFO      = 2
WARNING   = 3
ERROR     = 4
SOLUTION  = 5

# Puzzle part selection
PART1 = 1
PART2 = 2

# -------------------------------------------------
# Global configurations for the program and testing
# -------------------------------------------------
RunLevel                 = FULLINPUTRUN
Puzzle_part              = PART1
FullInputFileName        = 'input.txt'
SampleInputFileName      = 'sample.txt'
PrintInput               = False
WriteRunResults          = False
RemoveEOLFromInputLines  = True
ResultsOutputFileName    = 'out_1.txt'
LogPrintLevel            = SOLUTION
LogWriteLevel            = INFO
# -------------------------------------------------

# ----------------------------------------------------
# Functions and globals specific to the current puzzle
# ----------------------------------------------------
def puzzleSolution1(lines):
    # Ingredients : A list containing all ingredients that appear in the
    #               input file
    ingredients = getIngredients(lines)
    log(INFO,"Ingredients: " + str(ingredients))
    
    
    # Allergens : A list of all allergens that appear in the input file.
    allergens = getAllergens(lines)
    log(INFO,"Allergens: " + str(allergens))
    
    
    # CannotContain : A dictionary that maps an allergen and all the
    #                 ingredients that can not contain that allegen
    # Example: CannotContain[dairy] = ['k', 'sq', 'h'] means that none of 
    #           those ingredients can contain dairy
    cannotContain = buildCannotContain(allergens, ingredients, lines)
    
    
    # safeIngredients : a List of ingredients that contain no allergens
    safeIngredients = calculateSafeIngredients(ingredients, cannotContain)

    # ingredientsCount : The amount of times any of the safe ingredients
    #   appear in any ingredients list
    safeIngredientsCount = countSafeIngredientsInList(safeIngredients, lines)
    log(INFO,"Safe Ingredients: " + str(safeIngredients))
    
    log(INFO, "Day 21 Part 1: " + str(safeIngredientsCount))
    
    puzzleSolution2(lines, ingredients, allergens, safeIngredients)

def puzzleSolution2(lines, ingredients, allergens, safeIngredients):
    log(INFO, "******* Solution of part 2")
    
    log(INFO, "Number of allergens: " + str(len(allergens)))
    log(INFO, "Number of safe ingredients: " + str(len(safeIngredients)))
    
    dangerousIngredients = calculateDangerousIngredients(ingredients, safeIngredients)
    log(INFO, "Dangerous Ingredients:\n" + str(dangerousIngredients))
    
    log(INFO, "******* Rewriting ingredients lists without safe ingredients")
    dangerousLines = writeIngredientsListsWithoutSafeIngredients(lines, dangerousIngredients)
    for line in dangerousLines:
        log(INFO, line)
    
    # Convert the file lines into a data structure
    # List of Lists, where each list consists of:
    #   - List of dangerous ingrendients
    #   - List of allergens
    ingredientsAndAllergens = buildIngredientsAndAllergens(lines, dangerousIngredients)
    log(INFO, "Ingredients and allergens:\n" + str(ingredientsAndAllergens))
    
    # Find the correct mapping of ingredients to allergens
    correctMapping = findCorrectAllergenMapping(allergens, dangerousIngredients, ingredientsAndAllergens)
    # Sort the ingredients in lexicographic order
    sortedIngredients = sortIngredientsByAllergen(correctMapping)
    log(SOLUTION, "Day 21 Part 2: " + sortedIngredients)

def sortIngredientsByAllergen(mapping):
    sortedAllergens = sorted(list(mapping.keys()))
    print(sortedAllergens)
    sortedIngredients = ""
    for allergen in sortedAllergens:
        sortedIngredients += mapping[allergen] + ","
    return sortedIngredients[:-1]
    
def findCorrectAllergenMapping(allergens, dangerousIngredients, ingredientsAndAllergens):
    mappings = list(permutations(allergens))
    for mapping in mappings:
        mappingDict = {}
        for index in range(len(allergens)):
            allergensPermutation = mapping[index]
            ingredient = dangerousIngredients[index]
            mappingDict[allergensPermutation] = ingredient
            
        # Verify if mapping satisfies all constraints
        if (mappingSatisfiesConstraints(mappingDict, ingredientsAndAllergens)):
            return mappingDict

def mappingSatisfiesConstraints(mappingDict, ingredientsAndAllergens):
    # As soon as one constrain is not satisfied, return False
    for line in ingredientsAndAllergens:
        allergensInLine = line[1]
        ingredientsInLine = line[0]
        
        # For every allergen, its associated ingredient should be in the list
        for allergen in allergensInLine:
            requiredIngredient = mappingDict[allergen]
            if not requiredIngredient in ingredientsInLine:
                return False
    return True

def buildIngredientsAndAllergens(lines, dangerousIngredients):
    ingredientsAndAllergens = []
    
    for line in lines:
        dangerousIngredientsInLine = []
        lineIngredients = getIngredientsInLine(line)
        lineAllergens   = getAllergensInLine(line)
        for ingredient in lineIngredients:
            if ingredient in dangerousIngredients:
                dangerousIngredientsInLine.append(ingredient)
        ingredientsAndAllergens.append([dangerousIngredientsInLine, lineAllergens])
    
    return ingredientsAndAllergens

def calculateDangerousIngredients(ingredients, safeIngredients):
    dangerousIngredients = []
    
    for ingredient in ingredients:
        if not ingredient in safeIngredients:
            dangerousIngredients.append(ingredient)
    
    return dangerousIngredients

def getIngredients(lines):
    ingredients = []
    for line in lines:
        ingredientsStringInLine = line.split(" (")[0]
        ingredientsInLineList   = ingredientsStringInLine.split(' ')
        log(DEBUG, ingredientsStringInLine)
        for ingredient in ingredientsInLineList:
            if not ingredient in ingredients:
                ingredients.append(ingredient)
    return ingredients
    
def getAllergens(lines):
    allergens = []
    for line in lines:
        allergensStringInLine = line.split("(contains ")[1]
        allergensStringInLine = allergensStringInLine.split(")")[0]
        allergensInLineList   = allergensStringInLine.split(', ')
        log(DEBUG, allergensInLineList)
        for allergen in allergensInLineList:
            if not allergen in allergens:
                allergens.append(allergen)
    return allergens
    
def buildCannotContain(allergens, ingredients, lines):
    # an ingredient goes to the cannotContain list for a given allergen
    # unles it appears in all the lists in which a the allergen is mentioned
    cannotContain = {}
    for allergen in allergens:
        cannotContainIngredients = []
        for ingredient in ingredients:
            # Checking if ingredient can or can not contain the allergen
            for line in lines:
                if (doesLineContainAllergen(line, allergen)):
                    if (not doesLineContainIngredient(line, ingredient)):
                        if not ingredient in cannotContainIngredients:
                            cannotContainIngredients.append(ingredient)
        cannotContain[allergen] = cannotContainIngredients
    return cannotContain

def doesLineContainIngredient(line, ingredient):
    ingredientsStringInLine = line.split(" (")[0]
    ingredientsInLineList   = ingredientsStringInLine.split(' ')
    if not ingredient in ingredientsInLineList:
        return False
    else:
        return True

def doesLineContainAllergen(line, allergen):
    allergensStringInLine = line.split("(contains ")[1]
    allergensStringInLine = allergensStringInLine.split(")")[0]
    allergensInLineList   = allergensStringInLine.split(', ')
    if not allergen in allergensInLineList:
        return False
    else:
        return True

def calculateSafeIngredients(ingredients, cannotContain):
    # For an ingredient to be safe, it must be an element of all allergens
    # in the cannotContain dictionary
    safeIngredients = []
    for ingredient in ingredients:
        isIngredientSafe = True
        for allergenKey in cannotContain:
            elements = cannotContain[allergenKey]
            if not ingredient in elements:
                isIngredientSafe = False
        if isIngredientSafe:
            safeIngredients.append(ingredient)
    return safeIngredients

def countSafeIngredientsInList(safeIngredients, lines):
    count = 0
    for safeIngredient in safeIngredients:
        for line in lines:
            ingredientsStringInLine = line.split(" (")[0]
            ingredientsInLineList   = ingredientsStringInLine.split(' ')
            if safeIngredient in ingredientsInLineList:
                count += 1
    return count
    
def writeIngredientsListsWithoutSafeIngredients(lines, dangerousIngredients):
    newLines = []
    for line in lines:
        dangerousIngredientsInLine = []
        lineIngredients = getIngredientsInLine(line)
        lineAllergens   = getAllergensInLine(line)
        for ingredient in lineIngredients:
            if ingredient in dangerousIngredients:
                dangerousIngredientsInLine.append(ingredient)
        newLines.append(str(dangerousIngredientsInLine) + "=>" + str(lineAllergens))
    return newLines
        
def getIngredientsInLine(line):
    ingredientsStringInLine = line.split(" (")[0]
    ingredientsInLineList   = ingredientsStringInLine.split(' ')
    return ingredientsInLineList

def getAllergensInLine(line):
    allergensStringInLine = line.split("(contains ")[1]
    allergensStringInLine = allergensStringInLine.split(")")[0]
    allergensInLineList   = allergensStringInLine.split(', ')
    return allergensInLineList

# ------------------
# Global definitions
# ------------------
logStr = ""

def main():
    if (RunLevel == PROBETESTING):
        log(INFO, "******* Running Probe Testing...")
        
    fileLines = readRawLines(RemoveEOLFromInputLines)
        
    if (Puzzle_part == PART1):
        log(INFO, "******* Solution to part 1:")
        puzzleSolution1(fileLines)
    
    if (Puzzle_part == PART2):
        log(INFO, "******* Solution to part 2:")
        puzzleSolution2(fileLines)

def readRawLines(stripEOL=False):
    fileName = ""
    if (RunLevel == SAMPLETESTING):
        fileName = SampleInputFileName
    if (RunLevel == FULLINPUTRUN):
        fileName = FullInputFileName
    
    log(INFO, "******* Reading from file " + fileName)
    with open(fileName, 'r') as file:
        raw_lines = file.readlines()
    
    # Remove EOL from lines
    strippedLines = []
    for line in raw_lines:
        strippedLines.append(line.rstrip('\n'))
        
    if (PrintInput):
        log(INFO, "******* Input:")
        for line in raw_lines:
            log(INFO, line.rstrip('\n'))
        log(INFO,"")
    log(INFO, "******* Read " + str(len(raw_lines)) + " lines.")
    
    if (stripEOL):
        return strippedLines
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
    log(INFO, "******* Writing results to run_logfile.txt")
    with open("run_logfile.txt", 'w') as file:
        # Write data to logfile
        file.write(logStr)
        
if __name__ == "__main__":
    main()
    writeLogFile()
    
    

