/****************************************
 * C-ploration 10 for CS 271
 * 
 * [NAME] Curtis Kauer
 * [TERM] FALL 2023
 * 
 * Interface for error handling
 ****************************************/

#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/*
    enum exitcode - integer codes for retrieving error strings from *error_messages array in error.c 
    - codes start from 1
*/
enum exitcode{
    EXIT_INCORRECT_ARGUMENTS = 1,
    EXIT_CANNOT_OPEN_FILE,
    EXIT_TOO_MANY_INSTRUCTIONS,
    EXIT_INVALID_LABEL,
    EXIT_SYMBOL_ALREADY_EXISTS,
    EXIT_INVALID_A_INSTR,
    EXIT_INVALID_C_DEST,
    EXIT_INVALID_C_COMP,
    EXIT_INVALID_C_JUMP,
    EXIT_INVALID_FILE
};

//function prototypes

/*
    exit_program - terminates the program and outputs the error in arg1
    arg1 - enum exitcode code - the exitcode (index) of the error string to output from *error_messages array in error.c
    arg2...arg# - any other number of arguments to be outputted along with the error string
    return - void - returns nothing
*/
void exit_program(enum exitcode code, ...);

#endif