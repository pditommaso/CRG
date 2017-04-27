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


arg1 = sys.argv[1]						#console input
arg = re.sub('\.dnd$', '', arg1)		#remove extension
argOut = arg+"-out.dnd"					#add output format

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
	

Phylo.write(treeResult, argOut, 'newick')

