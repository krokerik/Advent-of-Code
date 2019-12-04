import os
import sys

puzzle_input = '../input/'+os.path.basename(__file__)[3:5]+'.txt'
fp           = open(puzzle_input,'r')

# solution code begins

def is_part1(pwd):
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

def is_part2(pwd):
	res = [int(i) for i in str(pwd)]
	cur = 0
	repeats = False
	for i,left in enumerate(res):
		if i<5:
			right = res[i+1]
			if left == right:
				repeats = True
				cur += 1
			elif cur == 1: # the two adjacent matching digits are not part of a larger group of matching digits
				return True
			else:
				cur = 0
			if cur > 1:
				repeats = False
	return repeats

rang = fp.read().strip().split('-')
rang = list(map(int,rang))
part1 = 0
part2 = 0
for n in range(rang[0], rang[1]+1): # The value is within the range given in your puzzle input.
	if is_part1(n):
		part1 += 1
		if is_part2(n):
			part2 += 1
print("part 1: " + str(part1))
print("part 2: " + str(part2))
