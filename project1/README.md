# Computer Archetecture Project 1
## Jiawei Jiang

# Build
Use "make" to build executable file, you should get a executable file called "driver" in makefile directory.

# Run
    ./driver *([-options] [paramter])

Include 5 options:

    [-c     1024 ]  cache size in bytes, default:65536
    [-b      64  ]  block size in bytes, default:64
    [-n      2   ]  n-way associativity, default:2
    [-r     LRU  ]  repalcement policy(random/FIFO/LRU), default:LRU
    [-a     mxm  ]  algorithms(dot, mxm, mxm_block), default:mxm
      
See help by:

    ./driver -h

Program will return 5 metrics:
    
    Read hits
    Read misses
    Write hits
    Write misses
    Instruction count
Note:       
The size of array is 1000.      
The matrix is 200*200.      
Chunk size is 20.       
These parameters can not be changed by command line.  

# Functionality
Emulator can simulate 3 algorithms.     
1. Dot multiplication       
2. Matrix multiplication        
3. Matrix multiplication with chunks    


# Analysis
Take "mxm" algorithm as example.
## Different cahce associativities
Set

    c = 1024
    b = 64
    r = LRU
    a = mxm

And change the value of n.   

n |  1 |  2  | 16
-- | -- | -- | --
read_ints  | 43089 |  3529738 |6562472
read_misses |15956911|    12470262   | 9437528
write_hits | 0|   0 |  0
write_misses  |  40000  | 40000   |40000
instructions  |  32040000  |  32040000  |  32040000


Hit rate increases from direct-mapped to fully associative.

## Different cache repalcement policies
I think it should be some difference between them and LRU should be the better one. However, my program shows little difference. So I think my program may still have some bugs waiting to be fixed. :(

## Different block sizes

Set

    c = 1024
    n = 2
    r = LRU
    a = mxm

And change the value of b.   

b |  8  | 64 | 128
-- | -- | -- | --
read_ints |  25074 |  3529738 |3769666
read_misses| 15974926   | 12470262   | 12230334
write_hits | 0  | 0   |0
write_misses |   40000  | 40000  | 40000
instructions  |  32040000 |   32040000 |  32040000

Hit rate increases while block size increases.


##Different total cache sizes
Test metrix has 200*200 elements, so we assume that cache larger than 1Kb satisfies the requirements.       
Set

    b = 64
    n = 2
    r = LRU
    a = mxm

And change the value of c.   

c  | 1024  |  4096  |  16384
-- | -- | -- | --
read_ints |  3529738| 3631746 |4002876
read_misses| 12470262  |  12368254  |  11997124
write_hits  |0  | 0  | 14
write_misses  |  40000  | 40000  | 39986
instructions  |  32040000  |  32040000   | 32040000

Hit rate increases while cache sizes increases.