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
	return io.get()

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

def run(program, position=0):
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

		output = program[position+argc]
		res    = operation(input)
		if opcode is 4:
			return (position+argc+1, program)
		if type is 1:
			if res is True:
				position = input[1]
			else:
				position += argc+1
		else:
			program[output] = res
			position += argc+1

	return (-1,program)

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
phases   = list(itertools.permutations([0,1,2,3,4]))
phases2  = list(itertools.permutations([5,6,7,8,9]))

for program in programs:
	outputs = []
	for setting in phases:
		io.queue.clear()
		input = 0
		for amp in setting:
			io.put(amp)
			io.put(input)
			run(program)
			input = io.get()
		outputs.append(input)
	print("part 1:",max(outputs))

	outputs = []
	for setting in phases2:
		io.queue.clear()
		input     = 0
		positions = []
		states    = []
		halted    = False
		for amp in setting:
			io.put(amp)
			io.put(input)
			res = run(program)
			positions.append(res[0])
			states.append(res[1])
			input = io.get()
		while not halted:
			for i,state in enumerate(states):
				io.put(input)
				res = run(state,positions[i])
				states[i]    = res[1]
				if res[0] is -1:
					positions[i] = 0
					if i is 4: #if it is last amp
						halted = True
				else:
					positions[i] = res[0]
				input = io.get()
		outputs.append(input)
	print("part 2:",max(outputs))
