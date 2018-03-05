# MIPS matrix multiplication

## main.asm
### Functionality
1. Read 2 input matrices from file, ```A.in``` and ```B.in```       
2. Calculate the matrix multiplication.     
3. Write result into file ```C.out```

### Environment
Test passed under:
```
QTspim 9.1.20
Ubuntu 16.04.9
```

P.S. To run proc under mac, changing input/output paths to absolute ones may help.

## python files
Provide a series of python file for test.       

### in.py
Create input matrices.      
Run it by:      ```python in.py [filename...]```        
e.g. ```python in.py A.in B.in```

### out.py
Print the matrix by ```python out.py [filename]```

### compare.py
Run ```python compare.py``` to calculate the matrix multiplication of the matrices in ```A.in``` and ```B.in```, then compare it with the output of ```C.out```.        
Tested the correctness of MIPS proc.      
NOTE: library`numpy` is required.