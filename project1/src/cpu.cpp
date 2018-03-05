#include "cpu.h"
#include "address.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;


Cpu::Cpu(int c, int b, int n, string r): Cache(c, b, n, r), instructions(0){
	//create a dummy instance to call init()
	Address a(0);
	a.init(n, b);
}


void Cpu::dot(int n){
	//store addresses
	Array a(n), b(n);
	for(int i=0; i<n; i++){
		a[i] = Address(i);
		b[i] = Address(n + i);
	}

	Address c;

	//init ram values
	for(int i=0; i<n; i++){
		set_double(a[i], i);
		set_double(b[i], 2*i);
	}

	//init cache
	clear_cache();
	instructions = 0;

	//main loop
	double ci = 0;
	for(int i=0; i<n; i++){
		int v1 = get_double(a[i]);
		int v2 = get_double(b[i]);
		ci += v1 * v2;
		instructions += 3;
	}
	set_double(c, ci);
	instructions++;

	log();

}

 
void Cpu::mxm(int n){
	//store addresses
	Array a(n*n), b(n*n), c(n*n);
	for(int i=0; i<n*n; i++){
		a[i] = Address(i);
		b[i] = Address(n*n + i);
		c[i] = Address(2*n*n + i);
	}
	//init ram values
	for(int i=0; i<n*n; i++){
		set_double(a[i], i);
		set_double(b[i], 2*i);
		set_double(c[i], 3*i);
	}

	//init cache
	clear_cache();
	instructions = 0;

	//main loop
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			double cij = 0;
			for(int k=0; k<n; k++){
				cij += get_double(a[i+k*n]) * get_double(b[k+j*n]);
				instructions += 4;
			}
			set_double(c[i+j*n], cij);
			instructions++;
		}
	}

	log();
}


void Cpu::mxm_block(int n){
	//store addresses
	Array a(n*n), b(n*n), c(n*n);
	for(int i=0; i<n*n; i++){
		a[i] = Address(i);
		b[i] = Address(n*n + i);
		c[i] = Address(2*n*n + i);
	}

	//init ram values
	for(int i=0; i<n*n; i++){
		set_double(a[i], i);
		set_double(b[i], 2*i);
		set_double(c[i], 3*i);
	}

	//init cache
	clear_cache();
	instructions = 0;

	//main loop
	for(int si=0; si<n; si+=10){
		for(int sj=0; sj<n; sj+=10){
			for(int sk=0; sk<n; sk+=10){
				do_block(n, si, sj, sk, a, b, c);
			}
		}
	}

	log();
}


void Cpu::do_block(int n, int si, int sj, int sk, Array& a, Array& b, Array& c){
	for(int i=si; i<si+10; i++){
		for(int j=sj; j<sj+10; j++){
			double cij = get_double(c[i+j*n]);
			instructions++;
			for(int k=sk; k<sk+10; k++){
				cij += get_double(a[i+k*n]) * get_double(b[k+j*n]);
				instructions += 4;
			}
			set_double(c[i+j*n], cij);
			instructions++;
		}
	}
}


void Cpu::log(){
	cout<<"read_hit :\t"<<read_hit<<endl;
	cout<<"read_miss:\t"<<read_miss<<endl;
	cout<<"write_hit :\t"<<write_hit<<endl;
	cout<<"write_miss:\t"<<write_miss<<endl;
	cout<<"instructions:\t"<<instructions<<endl;
}