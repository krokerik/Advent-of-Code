import os
import sys

puzzle_input = '../input/'+os.path.basename(__file__)[3:5]+'.txt'
fp           = open(puzzle_input,'r')

# solution code begins

def parseWire(input):
	obj = {"direction":input[0],"distance":int(input[1:])}
	return obj
dx = {'R':1,'U':0,'L':-1,'D':0}
dy = {'R':0,'U':1,'L':0,'D':-1}

wires = [[parseWire(m) for m in n.split(',')] for n in fp.read().split() if n.strip()]
positions = []
for wire in wires:
	position = [0,0]
	wire_positions = []
	for instruction in wire:
		for n in range(instruction["distance"]):
			position[0] += dx[instruction["direction"]]
			position[1] += dy[instruction["direction"]]
			wire_positions.append(tuple(position.copy()))
	positions.append(wire_positions)

intersections = list(set(positions[0]) & set(positions[1]))

lowest       = sys.maxsize
lowest_steps = sys.maxsize

for intersection in intersections:
	absolute = list(map(abs,intersection))
	dist     = abs(0-intersection[0]) + abs(0-intersection[1])
	steps    = positions[0].index(intersection) + positions[1].index(intersection) + 2 #add 2 for missing start position
	lowest       = dist if dist<lowest else lowest
	lowest_steps = steps if steps<lowest_steps else lowest_steps

print("part 1: "+str(lowest))
print("part 2: "+str(lowest_steps))
