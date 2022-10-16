from igraph import Graph, mean
import numpy as np

import matplotlib.pyplot as plt
import math

def Graph_file_gen(g,new_file_name):

	with open(new_file_name,'w') as f:
		for n in g.vs:
			f.write(str(n.index) + '|')
			for ne in n.neighbors():
				f.write( str(ne.index) +' ')
			f.write('\n')

def main():
	N = 5000
	deg = 3

	
#	neis = g.vs[0].neighbors()

#	for neis in g.vs:
#		print(neis.index)
#		for ne in neis.neighbors():
#			print(ne.index)

	#print( sum(g.degree())/len(g.degree() ) )

	for i in range(1000):
		#m = list(np.random.poisson(deg,N))
		#g = Graph.Static_Power_Law(N,deg * N , 3)
		g = Graph.Barabasi(N,deg)

		new_file_name = 'graph_' + str(i).zfill(3) + '.dat'
		Graph_file_gen(g,new_file_name)

		deg_seq = sorted( g.degree(),reverse = True)

	'''
	dmax = max(deg_seq)

	ax = plt.subplot(111)
	box = ax.get_position()

	ax.plot(deg_seq,"b-",marker = "o")
	ax.set_yscale('log')
	ax.set_xscale('log')
	plt.show()
	'''
			

if __name__ == '__main__':
	main()