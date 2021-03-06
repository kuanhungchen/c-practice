# Storage Classes

## Introduction

Storage classes are used to describe/define the **scope**, **visibility** and **life-time** of a variable/function.

## Types

### auto

- This can only be used to define variables.
- This is the **default** for all variables declared inside a function or a block.
- Scope: within block
- Initial value: garbage
- Life: end of block

### extern

- This can be used to define functions or variables.
- When we declare an extern variable, the memory is not allocated for it until we define it.
- When to use:
    1. when need to use a function/variable (ex: `int c`) before declare it, then add `extern int c` before using it, compiler will go to find its declaration.
    2. when need to use a function/variable outside of file, e.g. a huge program may need cross-file variables.
- Scope: global, multiple files
- Initial value: zero
- Life: end of program

### static

- This can be used to define functions or variables.
- Static variables have a property of preserving their value even after they are out of their scope.
- Scope: within block
- Initial value: zero
- Life: end of program

### register

- This can only be used to define variables.
- Use this to ask compiler to try to store these variables in the register of the microprocessor if a free register is available.
- Usually few variables are to be accessed very frequently in a program are declared with the register keyword which improves the running time.
- Of course we cannot obtain the address of a register variable using pointers.
- Scope: within block
- Initial value: garbage
- Life: end of block
