#ifndef DATABLOCK_H
#define DATABLOCK_H

#include <vector>

using namespace std;

class Datablock{
public:
	Datablock();
	Datablock(int s);
	int size;
	int tag;
	int LRU;
	int FIFO;
	vector<double> data;
};


#endif