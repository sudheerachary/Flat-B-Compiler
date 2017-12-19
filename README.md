# Flat-B Language Compiler
Flat-B is a Programming Language mainly consists of declaration block where all the used variables are declared, code block consists of program logic expressed in multiple arithmetic expressions, assignments, different kind of loops.

## Dependencies

> [Flex - A Lexical Analyzer](https://en.wikipedia.org/wiki/Flex_(lexical_analyser_generator)). 
### **Install flex** 
    sudo apt install flex

> [Bison - A Parser Generator](https://www.gnu.org/software/bison/).
### **Install bison**
    sudo apt install bison
    
> [LLVM - A Low Level Virtual Machine Used for IR Generation](https://llvm.org/).
### **Install llvm**
[follow instruction here](https://apt.llvm.org/)

## Instructions to run
### Make the Flat-B Compiler
    make
    
### Run the Flat-B Compiler
    ./bcc.sh path_to_test_file
    
### View Generated IR
    ./bcc path_to_test_file
 
### Clean Generated Files
    make veryclean

