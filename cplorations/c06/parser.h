/****************************************
 * C-ploration 5 for CS 271
 * 
 * [NAME] Curtis Kauer
 * [TERM] FALL 2023
 * 
 ****************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH - 2

typedef int16_t hack_addr;
typedef int16_t opcode;

/*
instrumentType - determines if the instruction is A, C, or no type instruction
*/
typedef enum instrumentType{
    INVALID_INSTRUCTION = -1, A_TYPE_INSTRUCTION, C_TYPE_INSTRUCTION
}instrumentType;

/*
C_instruction- C instruction data type that holds the the a instruction code, the c instrusction code,  the destination code, and the jump code 
*/
typedef struct C_instruction{

    opcode a:1;
    opcode comp:6;
    opcode dest:3;
    opcode jump:3;

}C_instruction;

/*
A_instruciton - A instruction data type that holds the address and label
*/
typedef struct A_instruction{
    union A_purpose{
        hack_addr address;
        char *label;
    };
    bool is_addr;
}A_instruction;

/*
Instruction - tells the instruciton type
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