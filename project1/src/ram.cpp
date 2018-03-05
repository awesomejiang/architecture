#include "ram.h"
#include "address.h"

Ram::Ram(int size):
	block_size(size/8),
	ram_data(10000000, Datablock(size/8)) 
{}

Datablock& Ram:: get_block(Address& addr){
	
	return ram_data[addr.get_addr()/block_size];
}

void Ram::set_block(Address& addr, Datablock& block){

	ram_data[addr.get_addr()/block_size] = block;
}