def get_next_position(current_position):
    new_position = [0, 0]
    # slope right 3, down 1
    new_position[0] = current_position[0] + 3
    new_position[1] = current_position[1] + 1
    return new_position

def get_map_element(map, map_width, position):
    x = position[0] % map_width # Map repeats itself indefinitely
    y = position[1]
    
    return map[y][x]

def main():
    file = open('input_day3.txt', 'r')
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
        
    # get_map_element function
    position = [0, 0]
    element = ''
    
    #print("Counting trees!")
    element = get_map_element(Map, MapWidth, position)
    counter = 0
    #print("Line 0: " + element)
    for i in range(MapHeight-1):
        position = get_next_position(position)
        element = get_map_element(Map, MapWidth, position)
        if (element == '#'):
            counter += 1
        #print("Line " + str(i+1) + ": " + element)
    print("Day 3 part 1 Solution: " + str(counter))

if __name__ == "__main__":
    main()