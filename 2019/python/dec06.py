import os

puzzle_input = '../input/'+os.path.basename(__file__)[3:5]+'.txt'
fp           = open(puzzle_input,'r')

# solution code begins

class planet:
	def __init__(self,name,parent):
		self.name     = name
		self.parent   = parent
		self.children = []
		self.visited  = 0

	def getOrbits(self):
		if self.parent is None:
			return 0
		else:
			return 1 + self.parent.getOrbits()

	def getDistance(self,target):
		self.visited = 1
		if self.name == target:
			return 0
		distances = []
		targets   = self.children.copy()
		if self.parent is not None:
			targets.append(self.parent)
		for child in list(filter(lambda x: x.visited != 1, targets)):
			distances.append(1 + child.getDistance(target))
		if not distances:
			return len(planets)+1 # max(?)
		return min(distances)

orbits  = [[m for m in n.strip().split(')')] for n in fp.read().split() if n.strip()]
planets = []

for orbit in orbits:
	parent = next((x for x in planets if x.name == orbit[0]),None)
	if parent is None:
		parent = planet(orbit[0],None)
		planets.append(parent)

	child = next((x for x in planets if x.name == orbit[1]),None)
	if child is None:
		child = planet(orbit[1],parent)
		planets.append(child)
		child.parent = parent
	else:
		child.parent = parent
	parent.children.append(child)

numOrbits = 0
for p in planets:
	numOrbits += p.getOrbits()
print("part 1:",numOrbits)

start = next((x for x in planets if x.name == "YOU"))
print("part 2:",start.getDistance("SAN") - 2)
