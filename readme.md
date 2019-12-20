# Computing System Architecture
## Lab 2
### Compile & Build
```bash
g++ branchsimulator.cpp -o branchsimulator.out
```
### Execution
A file called branchsimulator.out will be created in the folder. Use following shell to run it:
```bash
./branchsimulator.out config.txt trace.txt
```
> config.txt: first line -> m
>             second line -> k  
> 
> Smallest int number for m and k should be 1. However, the program could still handle k=0 and output prediction result. But it's not recommended.
### Output file
After above command lines, the program should output an file called trace.txt.out containing branch prediction result.
> If you prefer output filename being trace.out, please uncomment 38 and 39 lines of branchsimulator.cpp