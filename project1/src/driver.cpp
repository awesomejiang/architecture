#include "cpu.h"

#include <unistd.h>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// the usage 
void usage(string program){
	cout<<"Program Usage:\t"<<program<<endl
		<<"[-c     1024 ]  cache size in bytes, default:65536"<<endl
		<<"[-b      64  ]  block size in bytes, default:64"<<endl
		<<"[-n      2   ]  n-way associativity, default:2"<<endl
		<<"[-r     LRU  ]  repalcement policy(random/FIFO/LRU), default:LRU"<<endl
		<<"[-a     mxm  ]  algorithms(dot, mxm, mxm_block), default:mxm"<<endl
		<<endl;

	exit(1);
}


// function to get system arguments from command line
void getMyArgs(int argc, char** argv, int* c, int* b, int* n,
				string* replace, string* algo){	
    char ch;
    while (( ch = getopt(argc, argv, "c:b:n:r:a:h")) != -1){
        switch (ch){
        case 'c':
            *c = atoi(optarg);break;
        case 'b':
            *b = atoi(optarg);break;
        case 'n':
            *n = atoi(optarg);break;
        case 'r':
            *replace = string(optarg);break;
        case 'a':
            *algo = string(optarg);break;
        case 'h':
            usage(string(argv[0]));
        case '?':
            usage(string(argv[0]));
        }
    }
}



// the main program
int main(int argc, char* argv[]){				
	//set random seed
	srand(time(nullptr));

    //for parameters
	int c = 1024;
	int b = 64;
	int n = 2;
	string r = "LRU";
	string a = "mxm";

	getMyArgs(argc, argv, &c, &b, &n, &r, &a);

	Cpu cpu(c, b, n, r);
	if(a == "dot"){
		cpu.dot(1000);
	}
	else if(a == "mxm"){
		cpu.mxm(200);
	}
	else if(a == "mxm_block"){
		cpu.mxm_block(200);
	}
	else{
		cout<<"Undefined algorithm!"<<endl;
	}

	return 0;

}