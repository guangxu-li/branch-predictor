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
### Output file
After above command lines, the program should output an file called trace.txt.out containing branch prediction result.
> If you prefer output filename being trace.out, please uncomment 22 and 23 lines of branchsimulator.cpp