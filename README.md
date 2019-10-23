# 42-Corewar project
The corewar project is about a virtual arena for the [Corewar](https://en.wikipedia.org/wiki/Core_War) game where programs compete to take control over a virtual machine.
The competing programs are written in some kind of pseudo-assembly language code similar to real assembly code.
The project has two binaries :
* The assembler that builds the programs from an assembly source code.
* The emulator that runs the competing programs.
## Usage
Build project
```console
make
```
Create champion
```console
./asm/asm <champion.s>
```
Run the emulator
```console
./vm/corewar <champion1.cor> <champion2.cor>
```
## The virtual machine
### Processes
Processes are similar to threads and have their own context of registry values. There are 16 work registry for custom use and 1 "pc" (Program Counter) special registry that points to the next instruction to execute.
Processes are in parallel execution and each instruction take a certain number of cycle to complete. The fork and lfork instructions create a new process and thus take a long time to complete for the sake of game balance.
### General conception
Because of this repeating logic, we avoided repeating near-identical code in every functions like most 42/Epitech corewar projects did.
We created a generic_write() and generic_read() functions instead that makes our source code a lot of readable and maintainable.
### Operations
Upon executing an instruction, the machine runs following workflow :
* Reads one byte that determinates the instruction.
* (If needed by the instruction) reads one byte of parameter encoding. Indicates what type of parameters of varying size to use (registry number, constant value, value from memory).
* (If the parameter encoding byte is valid) reads and loads the parameter of varying size for the instruction execution.
* Selects the function responsible for the instruction. There is a function to every machine instruction (ld, st, zjmp, add, sub...) that all have the exact same signature (parameters type and return value), similar to interfaces in object oriented programming.
Most of these functions will need to read the actual values of parameters that were passed to them.
For instance, what happens upon reading parameters by the instructions:
If a registry number was specified, the relevant value is the value stored of the registry, not the registry number itself.
If a memory address value was specified, the relevant value is the value that is stored at the specified address, not the address itself.
If a direct value was specified, the relevant value is the value itself.
