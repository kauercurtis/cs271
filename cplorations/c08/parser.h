/****************************************
 * C-ploration 8 for CS 271
 * 
 * [NAME] Curtis Kauer
 * [TERM] FALL 2023
 * 
 ****************************************/
#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include "symtable.h"
#include "error.h"

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH - 2
#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

typedef int16_t hack_addr;
typedef int16_t opcode;

/*
InstructionType - determines the assembly instruction
*/
typedef enum instrumentType{

    INVALID_INSTRUCTION = -1, A_TYPE_INSTRUCTION, C_TYPE_INSTRUCTION

}instrumentType;

/*
C_instruction - encapsulation of a C type assembly instruction
*/
typedef struct C_instruction{

    opcode a:1;
    opcode comp:6;
    opcode dest:3;
    opcode jump:3;

}C_instruction;

/*
A_instruction - encapsulation of a A type assembly instruction
*/
typedef struct A_instruction{

    union A_purpose{
        hack_addr address;
        char *label;
    };
    bool is_addr;

}A_instruction;

/*
Instruction - encapsulation of an assembly instruction
*/
typedef struct Instruction{

    union Instruction_Type{

        A_instruction a_instruction;
        C_instruction c_instruction;
    };

    instrumentType instr_type;

}Instruction;

/** function prototypes **/
char *strip(char *s);

void parse(FILE * file);

bool is_Atype(const char*);

bool is_label(const char*);

bool is_Ctype(const char*);

char *extract_label(const char*, char*);

#endif