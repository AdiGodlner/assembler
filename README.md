# Simplified Assembly Language Assembler

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Usage](#usage)
- [Examples](#examples)
- [White Paper](#white-paper)

## Overview

The Assembler project, developed as part of the Systems Programming Lab course in the open university of Israel ( course number : [20465](https://www.openu.ac.il/courses/20465.htm) ) , is an assembler designed to translate simplified assembly language code into binary instructions. Based on the machine specifiactions given in the white paper

## Features

Key features of the assembler include macro unrolling, parsing of assembly instructions, encoding assembly instructions into binary representations, and comprehensive error handling.

## Usage

To run the assembler, provide a list of one or more source files to translate into binary. The assembler processes each file separately and generates the corresponding output files, as explained in the white paper.

## Examples

An example is included in the src file named `test1.asm`. You can run the example by providing the path to the file `test1.asm` as a command-line argument:

`assembler ./test1.asm`

## White Paper

The white paper provides details about the machine the assembler is designed for and the rules for translating different types of commands into binary. You can view the full white paper [here](./white_paper.pdf).

Some important specifications outlined in the white paper include:

- **Memory Size**: The machine has 256 frames, with each frame consisting of 14 bits.

- **Constraints**:
  
  - The machine supports only chars, strings, and integers; there is no support for real numbers.
  - The maximum length of a line in the input files is 80 characters.

- **Macro Constraints**:
  
  - There is no support for nested macros.
  - The name of a macro cannot be the same as the name of an instruction.
  - A macro is always defined before it is called.
  - The pre-assembler creates a new file with all the macros unrolled.

- **Error Handling**: If the assembler encounters an error, it will print a message to standard output with the line number that caused the error.

For further details and specifics, refer to the complete white paper. 
