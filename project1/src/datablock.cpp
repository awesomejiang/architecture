#include "datablock.h"

Datablock::Datablock():
	size(0), tag(-1), data(0), LRU(0), FIFO(0)
{}


Datablock::Datablock(int s):
	size(s), tag(-1), data(s, 0.0), LRU(0), FIFO(0)
{}