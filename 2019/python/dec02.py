import os
import itertools

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

for program_ in programs:
	program = program_.copy()
	position = 0
	program[1] = 12
	program[2] = 2
	while program[position] != 99:
		program[program[position+3]] = opcodes[program[position]](program[program[position+1]],program[program[position+2]])
		position += 4
	print("part 1: "+str(program[0]))

	inputs = list(itertools.product(range(0,100),range(0,100)))
	for input in inputs:
		position = 0
		program = program_.copy()
		program[1] = input[0]
		program[2] = input[1]
		while program[position] != 99:
			program[program[position+3]] = opcodes[program[position]](program[program[position+1]],program[program[position+2]])
			position += 4
		if program[0] == 19690720:
			print("part 2: " + str(100*input[0]+input[1]))
			break
