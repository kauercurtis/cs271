/****************************************
 * C-ploration 10 for CS 271
 * 
 * [NAME] Curtis Kauer
 * [TERM] FALL 2023
 * 
 * Interface for processing a HACK assembly file  
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
#include "hack.h"

// The maximum number of characters accepted from a HACK assembly line
#define MAX_LINE_LENGTH  200

// The maximum number of characters accepted from a HACK assembly label
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH - 2

// The 16 bit max address
#define MAX_HACK_ADDRESS INT16_MAX

// The maximum number of instructions that can be given from an 16 bit address
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

// 16 bit HACK instruction address
typedef int16_t hack_addr;

// 16 bit operation code
typedef int16_t opcode;

/*
    enum instructionType - Instruction types with associated decimal values
    - An invalid instruction = -1
    - A instruction = 0
    - C isntruction = 1
*/
typedef enum instructionType{
    INVALID_INSTRUCTION = -1, A_TYPE_INSTRUCTION, C_TYPE_INSTRUCTION
}instructionType;

/*
    C_instruction - encapsulation of a C type HACK assembly instruction
    field1 - opcode a - the a bit
    field2 - opcode comp - the computation id
    field3 - opcode dest - the destination id
    field4 - opcode jump - the jump id
*/
typedef struct C_instruction{
    opcode a:1;
    opcode comp:7;
    opcode dest:4;
    opcode jump:4;
}C_instruction;

/*
    A_instruction - encapuslation of a A type HACK assembly instruction
    field1 - union aType - hack_addr address = the 16 bit HACK instruction address - char *label = the label of the A instruction
    field2 - bool is_addr - true if A instruction is an address and false all other cases
*/
typedef struct A_instruction{
    union aType{
        hack_addr address;
        char *label;
    }aType;
    bool is_addr;
}A_instruction;

/*
    Instruction - encapsulation of an HACK assembly instruction
    field1 - union instruciton_type - A_instruction = the A instruction if instr_type = A_TYPE_INSTRUCTION (0) - C_instruction = the C instruction if instr_type = C_TYPE_INSTRUCTION (1) 
    field2 - instructionType instr_type - Either INVALID_INSTRUCTION (-1), A_TYPE_INSTRUCTION (0), C_TYPE_INSTRUCTION (1)
*/
typedef struct Instruction{
    union instruction_Type{
        A_instruction a_instruction;
        C_instruction c_instruction;
    }instruction_Type;

    instructionType instr_type;
}Instruction;

/** function prototypes **/


/*
    strip - removes whitespace and comments from a line in a HACK assembly file
    arg1 - char *s - the line to process
    return - char * - the line with all whitespace and comments removed
*/
char *strip(char *s);

/*
    parse - parses a HACK assembly file and gets the HACK instructions ready to assemble
    arg1 - FILE * file - the HACK assembly file to parse
    arg2 - Instruction *instructions - the array to hold all the parsed instructions
    return - int - the total number of instructions
*/
int parse(FILE * file, Instruction *instructions);

/*
    is_Atype - checks if a line is of A instruction type
    arg1 - const char* - the line to check
    return - bool - true if line is A instruction type, and false all other cases
*/
bool is_Atype(const char*);

/*
    is_label - checks if a line is a label
    arg1 - the line to check
    return - bool - true if line is a label and false all other cases
*/
bool is_label(const char*);

/*
    is_Ctype - checks if a line is of C instruction type
    arg1 - the line to check 
    return - bool - true if the line is C instruction type, and false all other cases
*/
bool is_Ctype(const char*);

/*
    extract_label - extracts the label name from a label line 
    arg1 - const char* line - the line to extract the label from
    arg2 - char* label - the string to hold the label name
    return - char* - the label name that is extracted
*/
char *extract_label(const char*, char*);

/*
    add_predefined_symbols - adds all 23 predefined HACK assembly symbols to hackArray in symtable.c
    return - void - returns nothing
*/
void add_predefined_symbols();

/*
    parse_A_instruction - parses an HACK assembly A type instruction for assembling
    arg1 - const char *line - the line to parse
    arg2 - A_instruction *instr - the A instruction instance to store the instruction after parsing
    return - bool - true if successfully parsed and false all other cases
*/
bool parse_A_instruction(const char *line, A_instruction *instr);

/*
    parse_C_instruction - parses an HACK assembly C type instruction for assembling
    arg1 - char *line - the line to parse
    arg2 - C_instruction *instr - the C instruction instance to store the isntruction after parsing
    return - void - returns nothing
*/
void parse_C_instruction(char *line, C_instruction *instr);

/*
    instruction_to_opcode - converts C instruction to opcode
    arg1 - C_instruction instr - the C instruction instance
    return - opcode - the 16 bit operation code
*/
opcode instruction_to_opcode(C_instruction instr);

/*
    assemble - assembles a collection of instructions into binary
    arg1 - const char * file_name - the name of the HACK assembly file
    arg2 - Instruction *instructions - an array of Instruction Instances
    arg3 - int num_instructions - the number of Instructions in the instructions array (arg2)
    return - void - returns nothing
    - Creates a .hack file of the HACK assembly file
*/
void assemble(const char * file_name, Instruction *instructions, int num_instructions);
#endif