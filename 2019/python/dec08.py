import os

puzzle_input = '../input/'+os.path.basename(__file__)[3:5]+'.txt'
fp           = open(puzzle_input,'r')

# solution code begins

images = [[int(m.strip()) for m in n.strip()] for n in fp.read().split() if n.strip()]

width      = 25
height     = 6
layer_size = width*height

for image in images:
	num_layers   = len(image)//layer_size
	fewest       = layer_size
	fewest_layer = []
	layers       = []
	for i in range(num_layers):
		layer = image[i*layer_size:i*layer_size+layer_size]
		layers.append(layer.copy())
		zeroes = layer.count(0)
		if zeroes < fewest:
			fewest = zeroes
			fewest_layer = layer
	print("part 1:",fewest_layer.count(1)*fewest_layer.count(2))
	final = [2]*layer_size
	for idx,layer in enumerate(layers):
		for pos,px in enumerate(layer):
			row    = pos // width
			column = pos %  width
			if px < 2 and final[pos] == 2:
				final[pos] = px
	print("part 2:")
	for i in range(height):
		for j in range(width):
			code = final[i*width+j]
			if code is 0:
				print(" ",end='')
			else:
				print("█",end='')
		print("")
