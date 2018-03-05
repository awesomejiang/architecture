#ifndef ADDRESS_H
#define ADDRESS_H

class Address{
public:
	Address();
	Address(int addr);

	static void init(int n, int b);
	
	int get_addr();
	int get_tag();
	int get_index();
	int get_offset();

private:
	int address;
	static int index; //decide which set
	static int offset; //decide which position in a block

};


#endif