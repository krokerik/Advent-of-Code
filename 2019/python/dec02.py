import os

puzzle_input = '../input/'+os.path.basename(__file__)[3:5]+'.txt'
fp           = open(puzzle_input,'r')

# solution code begins

def addition(first,second):
	return first+second

def multiplication(first,second):
	return first*second

opcodes = {
1:addition,
2:multiplication
}

programs = [[int(m.strip()) for m in n.split(',')] for n in fp.read().split() if n.strip()]

for program in programs:
	position = 0
	program[1] = 12
	program[2] = 2
	while program[position] != 99:
		program[program[position+3]] = opcodes[program[position]](program[program[position+1]],program[program[position+2]])
		position += 4
	print("part 1: "+str(program[0]))
