#ifndef RAM_H
#define RAM_H

#include <vector>
#include "datablock.h"
#include "address.h"

using namespace std;


class Ram{
public:
	Ram(int size);

	int block_size;

	Datablock& get_block(Address&);
	void set_block(Address&, Datablock&);

private:
	vector<Datablock> ram_data;

};

#endif