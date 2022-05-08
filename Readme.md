# Compiler Design Assignment

## Introduction
    Compiler made to convert C like code to xsm executable. 
    xsm executable can be directly run on xsm machine(https://exposnitc.github.io/). 

## How?

    Source code is converted to a Tree.

    Source code undergoes lexical analysis in which we detect "is program syntatically correct.". 
    If it not then exits with error.
    If no error , a tree is constructed with root node as program(main program). 

    Example

        Expression Node

                *
               / \
              4   5
    
    Code Generated for each node recursively

## Lexing program again?

    XSM don't have labels like nasm and all. 
    So labels should be changed according to program counter(instruction position).