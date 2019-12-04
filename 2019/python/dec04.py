import os
import sys

puzzle_input = '../input/'+os.path.basename(__file__)[3:5]+'.txt'
fp           = open(puzzle_input,'r')

# solution code begins

def is_valid(pwd):
	res = [int(i) for i in str(pwd)]
	if(len(res) != 6): # It is a six-digit number.
		return False
	repeats = False
	for i,left in enumerate(res):
		if i<5:
			right = res[i+1]
			if left > right: # Going from left to right, the digits never decrease
				return False
			if left == right: # Two adjacent digits are the same
				repeats = True
	return repeats

rang = fp.read().strip().split('-')
rang = list(map(int,rang))
valid = 0
for n in range(rang[0], rang[1]+1): # The value is within the range given in your puzzle input.
	if is_valid(n):
		valid += 1
print("part 1: " + str(valid))
