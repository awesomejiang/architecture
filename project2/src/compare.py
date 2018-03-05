import array
import sys
import numpy as np

a = array.array('i')
with open("A.in", 'r') as f:
	a.fromfile(f, 64)

b = array.array('i')
with open("B.in", 'r') as f:
	b.fromfile(f, 64)

c = array.array('i')
with open("C.out", 'r') as f:
	c.fromfile(f, 64)

na = np.matrix(np.reshape(a, (8, 8)))
nb = np.matrix(np.reshape(b, (8, 8)))
nc = np.matrix(np.reshape(c, (8, 8)))

if np.all((na*nb-nc)==0):
	print "MIPS mxm works well!"
else:
	print "MIPS mxm meets something wrong!"