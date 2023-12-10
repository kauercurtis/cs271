/****************************************
 * C-ploration 10 for CS 271
 * 
 * [NAME] Curtis Kauer
 * [TERM] FALL 2023
 * 
 * Implementation file for error.h
 ****************************************/
#include "error.h"

/*
    const char *error_messages - an array of error strings for exitcode in error.h 
*/
const char *error_messages[] =
{
    [EXIT_INCORRECT_ARGUMENTS] = "Usage: %s [filename]",
    [EXIT_CANNOT_OPEN_FILE] = "Cannot open file %s",
    [EXIT_TOO_MANY_INSTRUCTIONS] = "File contains more than the maximum of %u instructions.",
    [EXIT_INVALID_LABEL] = "Line %u: %s : Invalid label name",
    [EXIT_SYMBOL_ALREADY_EXISTS] = "Line %u: %s : Symbol is already defined",
    [EXIT_INVALID_A_INSTR] =  "Line %u: %s : Invalid A-instruction operand",
    [EXIT_INVALID_C_DEST] = "Line %u: %s : Invalid destination part of C-instruction",
    [EXIT_INVALID_C_COMP] = "Line %u: %s : Invalid compare part of C-instruction",
    [EXIT_INVALID_C_JUMP] = "Line %u: %s : Invalid jump part of C-instruction",
    [EXIT_INVALID_FILE] = "Invalid file: %s"
};

/*
    exit_program - terminates the program and outputs the error in arg1
    arg1 - enum exitcode code - the exitcode (index) of the error string to output from *error_messages array in error.c
    arg2...arg# - any other number of arguments to be outputted along with the error string
    return - void - returns nothing

    - terminates the program with call to exit()
*/
void exit_program(enum exitcode code, ...)
{
    va_list arguments;
    va_start(arguments, code);

    printf("ERROR: ");
    vfprintf(stdout, error_messages[code], arguments);
    printf("\n");

    va_end(arguments);
    exit(code);
}

