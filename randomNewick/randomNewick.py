'''
Input: Newick file (nwk extension) with a newick file
Output: Newick file '-out' with a new tree, with the same structure but with the leaves shuffled in a random way
'''
#!/usr/bin/python
from Bio import Phylo
from StringIO import StringIO

import sys
import random
import re								#regular expresion
import copy								#deep copy
import os								#file

'''	to read from a tree file by line arg
arg1 = sys.argv[1]						#console input
<<<<<<< HEAD
arg = re.sub('\.tree$', '', arg1)		#remove extension
argOut = arg+"_randome_out.tree"		#add output format
'''
files = [f for f in os.listdir('.') if (f.endswith('.tree') and not f.endswith('_random.tree'))]
=======
arg = re.sub('\.dnd$', '', arg1)		#remove extension
argOut = arg+"-random_out.dnd"					#add output format
>>>>>>> origin/master

for arg1 in files:
	arg = re.sub('.tree', '', arg1)		#remove extension
	argOut = arg+"_random.tree"			#add output format
	
	tree = Phylo.read(arg1, 'newick')
	treeResult = copy.deepcopy(tree)		#deep copy of the tree

	leaves = tree.get_terminals()
	leavesRandom = list(leaves) 			#copy by values
	i = 0

	random.shuffle(leavesRandom)
	'''
	#print leaves list
	print " --- leaves list ---"
	print " - ".join([str(x) for x in leaves] )
	print " -------------------"


	#print leaves list
	print " --- random list ---"
	print " - ".join([str(x) for x in leavesRandom] )
	print " -------------------"
	'''


	#recorrer el tree y modificar con el randomList
	for leaf in treeResult.get_terminals() :
		leaf.name = leavesRandom[i].name
		i= i+1
		
	#print tree
	Phylo.draw_ascii(tree)
			
	#print tree
	Phylo.draw_ascii(treeResult)	
		
	print('#######################')

	Phylo.write(treeResult, argOut, 'newick')

