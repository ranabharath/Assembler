# CS2102 Mini Project

## Project Overview
This project involves implementing an assembler for an extended SIMPLE instruction set, writing and testing programs in SIMPLE assembly, and developing an emulator for the SIMPLE machine.

## Features

### Assembler
- Reads assembly language from a text file
- Assigns label values and instruction opcodes
- Diagnoses common assembly errors (e.g., unknown instruction, missing label, duplicate label)
- Produces object file with machine code starting at address zero
- Generates a listing file showing instructions and addresses

### Assembler Testing
- Sample programs are provided for validation
- Additional programs were tested

### Bubble Sort in SIMPLE Assembly
- Implementation of bubble sort using the SIMPLE instruction set

### Emulator
- Partial functionality of the provided emulator
- Loads object files and executes test programs
- Supports memory dumping and error detection

## Instructions

### Assembler Usage
Compile the assembler using:
```sh
gcc asm.cpp -o asm
```
Run the assembler:
```sh
./asm input.asm
```

### Emulator Usage
Compile the emulator using:
```sh
gcc emu.cpp -o emu
```
Run the emulator:
```sh
./emu input.o
```

## File Structure
- `asm.cpp` - Source code for the assembler
- `emu.cpp` - Source code for the emulator
- `test1.asm`, `test2.asm`, ... - Sample assembly test files
- `test1.o`, `test2.o`, ... - Generated object files
- `test1.l`, `test2.l`, ... - Assembler listing files
- `claims.txt` - A list of project claims and functionalities implemented


