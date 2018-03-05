import array
import sys
filename = sys.argv[1]

a = array.array('i')
with open(filename, 'r') as f:
	a.fromfile(f, 64)

a = a.tolist()
l = [ a[i:i+8] for i in xrange(64) if i%8==0 ]

print "Read matrix from " + filename + ":"
for i in xrange(8):
	print l[i]