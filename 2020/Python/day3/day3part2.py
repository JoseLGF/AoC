def get_next_position_with_slope(current_position, slope_right, slope_down):
    new_position = [0, 0]
    
    new_position[0] = current_position[0] + slope_right
    new_position[1] = current_position[1] + slope_down
    return new_position

def get_map_element(map, map_width, map_height, position):
    x = position[0] % map_width # Map repeats itself indefinitely
    y = position[1]
    
    #print("y: " + str(y) + ", x: " + str(x))
    
    # In case of slopes greater than 1...
    if (y > map_height):
        return '.'
    
    return map[y][x]

def countTreesInMapWithSlope(map, map_width, map_height, slope_right, slope_down):
    #print("Counting trees in slope " + str(slope_right) + ", " + str(slope_down))
    
    position = [0, 0]
    element = ''
    element = get_map_element(map, map_width, map_height, position)
    counter = 0
    #print("Line 0: " + element)
    for i in range(map_height-1):
        position = get_next_position_with_slope(position, slope_right, slope_down)
        element = get_map_element(map, map_width, map_height, position)
        if (element == '#'):
            counter += 1
        #print("Line " + str(i+1) + ": " + element)
    #print("Found " + str(counter) + " trees for slope " + str(slope_right) + ", " + str(slope_down))  
    return counter

def main():
    # Open and read map file
    file = open('Input_day3.txt', 'r')
    #file = open('sample_day3.txt', 'r')
    MapLines = file.readlines()
    
    Map = []
    
    for line in MapLines:
        # Remove the trailing carriage retunr character
        Map.append(line.rstrip())
    
    MapWidth  = len(Map[0])
    MapHeight = len(Map)
    #print("Map width: " + str(MapWidth))
    #print("Map height: " + str(MapHeight))
        
    # Testing the get_next_position_with_slope function
    position = [0, 0]
    for i in range(MapHeight):
        position = get_next_position_with_slope(position, 3, 1)
        #print(position)
        
    

    """ START Here """
    
    slopes = [[1, 1],
              [3, 1],
              [5, 1],
              [7, 1],
              [1, 2]]
    trees_in_slopes = [0, 0, 0, 0, 0]
              
    for i in range(5):
        #print ("Iteration " + str(i))
        slope = slopes[i]
        slope_right = slope[0]
        slope_down  = slope[1]
        trees_in_slopes[i] = countTreesInMapWithSlope(Map, MapWidth, MapHeight, slope_right, slope_down)
     
    #print("Trees in slopes: " + str(trees_in_slopes))
    
    product = 1
    for trees_num in trees_in_slopes:
        product = product * trees_num
    print("Day 3 Part 2 Solution: " + str(product))
    
    

if __name__ == "__main__":
    main()