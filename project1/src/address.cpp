#include <cmath>
#include "address.h"


int Address::index;
int Address::offset;

Address::Address(): address(0) {}

Address::Address(int addr): address(addr) {}


void Address::init(int n, int b){
	static int flag = 0; //promise these func wont run twice.

	if(!flag){
		index = n;
		offset = b/8; //8 for doubles

		flag = 1;
	}
}


/**
 aaa   bbb   ccc
 tag  index offset
**/  


int Address::get_addr(){

	return address;
}


int Address::get_tag(){
	//get aaa
	return address/(index*offset);
}


int Address::get_index(){
	//get bbb
	return (address%(index*offset))/offset;
}


int Address::get_offset(){
	//get ccc
	return address%offset;
}