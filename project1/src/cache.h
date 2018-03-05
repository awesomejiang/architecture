#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <map>
#include <string>

#include "address.h"
#include "datablock.h"
#include "ram.h"

using namespace std;

class Cache: public Ram{
public:
	Cache(int c, int b, int n, string r);

	double get_double(Address&);
	void set_double(Address&, double);

	int read_hit;
	int read_miss;
	int write_hit;
	int write_miss;

	void clear_cache();

private:

	int num_sets;
	int num_blocks;

	vector< vector<Datablock> > cache_data;
	
	int count;

	string replacement;


	Datablock& replace(vector<Datablock>& set, Address& addr);
	Datablock& FIFO_block(vector<Datablock>& set);
	Datablock& LRU_block(vector<Datablock>& set);

};


#endif