SRC = $(wildcard ./src/*.h)
OBJ = $(patsubst %.h, %, $(notdir ${SRC}))
LNK = $(patsubst %.h, out/%.o, $(notdir ${SRC}))

all: out datablock address ram cache cpu driver


out:
	mkdir out

datablock: src/datablock.cpp | out
	g++ src/datablock.cpp -c -o out/datablock.o -std=c++11

address: src/address.cpp | out
	g++ src/address.cpp -c -o out/address.o -std=c++11

ram: src/ram.cpp out/datablock.o out/address.o | out
	g++ src/ram.cpp -c -o out/ram.o -std=c++11

cache: src/cache.cpp out/ram.o out/datablock.o out/address.o | out
	g++ src/cache.cpp -c -o out/cache.o -std=c++11

cpu: src/cpu.cpp out/cache.o out/address.o | out
	g++ src/cpu.cpp -c -o out/cpu.o -std=c++11


driver: src/driver.cpp out/cpu.o | out
	g++ src/driver.cpp $(LNK) -o driver -std=c++11

clean:
	rm -f -r out/ driver