#ifndef CPU_H
#define CPU_H

#include "address.h"
#include "cache.h"

typedef vector<Address> Array;

class Cpu: private Cache{
public:
	Cpu(int c, int b, int n, string r);


	void dot(int);
	void mxm(int);
	void mxm_block(int);

	void log();
private:

	int instructions;

	void do_block(int n, int si, int sj, int sk, Array& a, Array& b, Array& c);

};


#endif