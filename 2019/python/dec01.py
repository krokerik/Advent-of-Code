import os

puzzle_input = '../input/'+os.path.basename(__file__)[3:5]+'.txt'
fp           = open(puzzle_input,'r')

# solution code begins

modules = [int(n.strip()) for n in fp.read().split() if n.strip()]
total_fuel = 0
for module in modules:
	fuel = module//3 - 2 #floor division
	total_fuel += fuel
print("part 1: " + str(total_fuel))
