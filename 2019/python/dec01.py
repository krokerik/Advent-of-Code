import os

puzzle_input = '../input/'+os.path.basename(__file__)[3:5]+'.txt'
fp           = open(puzzle_input,'r')

# solution code begins

modules = [int(n.strip()) for n in fp.read().split() if n.strip()]
total_fuel      = 0
total_fuel_fuel = 0

def part1(wt):
	fuel = wt//3 - 2
	return fuel

def part2(wt):
	fuel = 0
	if wt > 0:
		fuel = wt//3 - 2
		fuel += part2(fuel)
	fuel = 0 if fuel<0 else fuel
	return fuel

for module in modules:
	fuel             = part1(module)
	fuel_fuel        = part2(module)
	total_fuel      += fuel
	total_fuel_fuel += fuel_fuel

print("part 1: " + str(total_fuel))
print("part 2: " + str(total_fuel_fuel))
