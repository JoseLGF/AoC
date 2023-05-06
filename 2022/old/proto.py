import pprint


file = open('input/day_03.txt', 'r')
Lines = temp = file.read().splitlines()


def chunks(lst, n):
    """Yield successive n-sized chunks from lst."""
    for i in range(0, len(lst), n):
        yield lst[i:i + n]

def priority(c):
    if ( (ord(c) >= ord('a') ) and (ord(c) <= ord('z'))):
        return ord(c) - ord('a') + 1
    if ( (ord(c) >= ord('A') ) and (ord(c) <= ord('Z')) ):
        return ord(c) - ord('A') + 27

groups = chunks(Lines,3)
#pprint.pprint(list(groups))

# for each group, find common token between the three elements of each group
badges = []
for group in groups:
    a = set(group[0])
    print(a)
    b = set(group[1])
    c = set(group[2])
    print(a & b)
    badges.append( list((a & b) & c)[0] )

print("badges:")
print(badges)

priorities = 0
for badge in badges:
    priorities += priority(badge)

print (priorities)