#include <cstdlib>
#include <vector>
#include <string>

#include "cache.h"
#include "address.h"
#include "datablock.h"

using namespace std;

Cache::Cache(int c, int b, int n, string r):
	num_sets(n),
	num_blocks(c/(b*n)),
	replacement(r),
	count(0),
	read_hit(0),
	read_miss(0),
	write_hit(0),
	write_miss(0),
	Ram(b),
	cache_data(n)
{}


double Cache::get_double(Address& addr){
	count++;

	auto obj_tag = addr.get_tag();
	vector<Datablock>& set = cache_data[addr.get_index()];

	//look up all blocks in target set -> HIT!
	for(auto &d: set){
		if(d.tag == obj_tag){
			read_hit++;
			d.LRU = count;

			return d.data[addr.get_offset()];
		}
	}

	//if no block found, read/replace a block into cache_data -> MISS!
	Datablock& new_block = replace(set, addr);

	new_block = get_block(addr);

	read_miss++;
	new_block.FIFO = count;
	new_block.LRU = count;
	return new_block.data[addr.get_offset()];

}


void Cache::set_double(Address& addr, double val){
	count++;

	auto obj_tag = addr.get_tag();
	vector<Datablock>& set = cache_data[addr.get_index()];

	int flag = 0;
	//look up all blocks in target set -> HIT!
	for(auto &d: set){
		if(d.tag == obj_tag){
			//modify d
			d.tag = addr.get_tag();
			d.data[addr.get_offset()] = val;
			d.LRU = count;

			//write through main memory
			set_block(addr, d);
			flag++;
			write_hit++;
			break;
		}
	}

	//if no block found, write/replace a block into cache_data -> MISS!
	if(!flag){
		//write allocate: read the address to cache first
		Datablock& new_block = replace(set, addr);
		new_block = get_block(addr);
		//and write through!
		new_block.tag = addr.get_tag();
		new_block.data[addr.get_offset()] = val;
		new_block.FIFO = count;
		new_block.LRU = count;
		set_block(addr, new_block);

		write_miss++;
	}

}



//3 different replacement methods
Datablock& Cache::replace(vector<Datablock>& set, Address& addr){
	if(set.size() < num_blocks){//set not full
		set.resize(set.size()+1);
		return set.back();
	}
	else{
		if(replacement=="random"){
			return set.at( rand()%set.size() );
		}

		if(replacement=="FIFO"){
			return FIFO_block(set);
		}

		if(replacement=="LRU"){
			return LRU_block(set);
		}	
	}
}


Datablock& Cache::FIFO_block(vector<Datablock>& set){
	auto &fifo_block = set.front();
	for(auto &block: set){
		if(block.FIFO < fifo_block.FIFO){
			fifo_block = block;
		}
	}

	return fifo_block;
}


Datablock& Cache::LRU_block(vector<Datablock>& set){
	auto &lru_block = set.front();
	for(auto &block: set){
		if(block.LRU < lru_block.LRU){
			lru_block = block;
		}
	}

	return lru_block;
}


void Cache::clear_cache(){
	read_hit = 0;
	read_miss = 0;
	write_hit = 0;
	write_miss = 0;
	count = 0;

	for(auto &vec: cache_data){
		vec.clear();
	}

}