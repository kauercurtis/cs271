/****************************************
 * C-ploration 8 for CS 271
 * 
 * [NAME] Curtis Kauer
 * [TERM] FALL 2023
 * 
 ****************************************/

#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/*
integer codes that correspond with *error_messages in error.c
*/
enum exitcode{

    EXIT_INCORRECT_ARGUMENTS = 1,
    EXIT_CANNOT_OPEN_FILE,
    EXIT_TOO_MANY_INSTRUCTIONS,
    EXIT_INVALID_LABEL,
    EXIT_SYMBOL_ALREADY_EXISTS,
    EXIT_INVALID_A_INSTR,

};

//function prototypes
void exit_program(enum exitcode code, ...);

#endif