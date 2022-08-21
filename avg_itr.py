import sys
import numpy as np
import os
#import matplotlib.pyplot as plt
from collections import defaultdict

def read_a_type(Dname, filename):
	#b_10_r1_050_000.dat
	r1_list = []
	iter_dict = {}
	iter_dict = defaultdict(lambda:{},iter_dict)

	cycle_num = 0
	#iter_dic[a][b], a is the number of iteration and b is the number of group

	for root,dirs,files in sorted(os.walk(Dname,topdown = False)):
		for name in sorted(files):
			#b_10_r1_050_000.dat
			#0123456789012345678
			n_end = 11 + len(name) - 19
			if name[0:n_end] != filename[0:n_end]:
				continue
            
			with open(os.path.join(root, name)) as f:
				print(name)
				num_round = 0
				lines = f.readlines()
				for line in lines:
					bk_line = line.split('|')
					itr_num = int(bk_line[0])
					if itr_num == 0:
						num_round += 1

					gsize = bk_line[2].split()
					for ele in gsize:
						gp, avg = int(ele.split(':')[0]), float(ele.split(':')[1])

						if gp not in iter_dict[itr_num]:
							iter_dict[itr_num][gp] = avg
						else:
							iter_dict[itr_num][gp] += avg
				
				cycle_num += num_round


	for iters in iter_dict:
		for gp in iter_dict[iters]:
			iter_dict[iters][gp] /= cycle_num

	return iter_dict



def main():
	done_file = []
	Der_name = sys.argv[1]
	dist_dir = sys.argv[2]

	for root,dirs,files in sorted(os.walk(Der_name,topdown = False)):
		for name in sorted(files):
			#b_10_r1_050_000.dat
			#0123456789012345678
			n_end = 11 + len(name) - 19
            if name[0:n_end] in done_file:
            	continue
			#print(name[0:11])
			one_content = read_a_type(Der_name, name)
			done_file.append(name[0:n_end])

			new_file_name = dist_dir + '/' + name[0:n_end] + '.dat'
			with open(new_file_name,'w') as f:
				for itr in one_content:
					f.write(str(itr) + '|')
					for gp in one_content[itr]:
						f.write( str(gp) + ':' + str(one_content[itr][gp]) + ' ')
					f.write('\n')


if __name__ == '__main__':
	main()
