import os
import itertools
import queue

puzzle_input = '../input/'+os.path.basename(__file__)[3:5]+'.txt'
fp           = open(puzzle_input,'r')

# solution code begins

def addition(input):
	return input[0]+input[1]

def multiplication(input):
	return input[0]*input[1]

def input(data):
	test = io.get()
	return test

def output(data):
	io.put(data[0])
	return data[0]

def jump_if_true(data):
	return data[0] != 0

def jump_if_false(data):
	return data[0] == 0

def less_than(data):
	return data[0] < data[1]

def equals(data):
	return data[0] == data[1]

def run(program, input1=None, input2=None):
	if input1 is not None:
		program[1] = input1
	if input2 is not None:
		program[2] = input2

	position = 0

	while program[position] != 99:
		instruction = [int(i) for i in str(program[position])]
		opcode      = int("".join(map(str,instruction[-2:])))
		operation   = opcodes[opcode][0]
		argc        = opcodes[opcode][1]
		type        = opcodes[opcode][2]
		input       = []

		while len(instruction) < argc+2:
			instruction.insert(0,0)
		for i,j in enumerate(reversed(instruction[:-2])):
			if j is 0:
				input.append(program[program[position+i+1]])
			elif j is 1:
				input.append(program[position+i+1])

		output    = program[position+argc]
		res = operation(input)
		if type is 1:
			if res is True:
				position = input[1]
			else:
				position += argc+1
		else:
			program[output] = res
			position += argc+1

	return program[0]

opcodes = { #(function, argc, type)
1:(addition,3,0),
2:(multiplication,3,0),
3:(input,1,0),
4:(output,1,0),
5:(jump_if_true,2,1),
6:(jump_if_false,2,1),
7:(less_than,3,0),
8:(equals,3,0)
}

io = queue.Queue()

programs = [[int(m.strip()) for m in n.split(',')] for n in fp.read().split() if n.strip()]

for program_ in programs:
	program = program_.copy()
	io.queue.clear()
	io.put(1)
	run(program)
	part1 = 0
	while not io.empty():
		part1 = io.get()
	print("part 1: "+str(part1))
	program = program_.copy()
	io.queue.clear()
	io.put(5)
	run(program)
	part2 = 0
	while not io.empty():
		part2 = io.get()
	print("part 2: "+str(part2))
