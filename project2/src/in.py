import array
import random
import sys

#read filenames from argv
for filename in sys.argv[1:]:
	#create a random value matrix
	l = [ random.randint(-100, 100) for i in xrange(64) ]

	a = array.array('i', l)
	with open(filename, 'wb') as f:
		a.tofile(f)

	#print matrix info to cout
	l = [ l[i:i+8] for i in xrange(64) if i%8==0 ]
	print "Write matrix into " + filename + ":"
	for i in xrange(8):
		print l[i]
	print