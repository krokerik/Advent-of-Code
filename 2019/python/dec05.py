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
	print("queue got",test)
	return test

def output(data):
	io.put(data[0])
	print("output: ",data[0])
	return data[0]

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
		input       = []

		while len(instruction) < argc+2:
			instruction.insert(0,0)
		for i,j in enumerate(reversed(instruction[:-2])):
			if j is 0:
				input.append(program[program[position+j+1]])
			elif j is 1:
				input.append(program[position+j+1])

		output    = program[position+argc]
		res = operation(input)
		program[output] = res
		position += argc+1

	return program[0]

opcodes = { #(function, argc)
1:(addition,3),
2:(multiplication,3),
3:(input,1),
4:(output,1)
}

io = queue.Queue()

programs = [[int(m.strip()) for m in n.split(',')] for n in fp.read().split() if n.strip()]

for program_ in programs:
	program = program_.copy()
	io.queue.clear()
	io.put(1)
	print("part 1: "+str(run(program)))
	while not io.empty():
		print(io.get())
