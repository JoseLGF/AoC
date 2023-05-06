with open('./../input/day_05.txt') as f:
    lines = [line for line in f]

stacks = [
    [*'QSWCZVFT'],
    [*'QRB'],
    [*'BZTQPMS'],
    [*'DVFRQH'],
    [*'JGLDBSTP'],
    [*'WRTZ'],
    [*'HQMNSFRJ'],
    [*'RNFHW'],
    [*'JZTQPRB']
]

operations = []
for line in lines:
    line = line.rstrip().split(' ')
    if(line[0] == "move"):
        operation = []
        operation.append(int(line[1]))
        operation.append(int(line[3]))
        operation.append(int(line[5]))
        operations.append(operation)
# print(operations)

# Part1
# for operation in operations:
#     amount = operation[0]
#     source = operation[1] - 1
#     target = operation[2] - 1
#     for i in range(amount):
#         element = stacks[source].pop()
#         stacks[target].append(element)

# Part 2
for operation in operations:
    amount = operation[0]
    source = operation[1] - 1
    target = operation[2] - 1
    intermediate_stack = []
    for i in range(amount):
        element = stacks[source].pop()
        intermediate_stack.append(element)
    for i in range(amount):
        element = intermediate_stack.pop()
        stacks[target].append(element)


message = []
for stack in stacks:
    message.append(stack[-1])

def convert(s):
    # initialization of string to ""
    new = ""
    # traverse in the string
    for x in s:
        new += x
    # return string
    return new

print(convert(message))