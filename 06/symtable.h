/****************************************
 * C-ploration 10 for CS 271
 * 
 * [NAME] Curtis Kauer
 * [TERM] FALL 2023
 * 
 ****************************************/
#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

// Maximum number of Symbol instances to store in hashArray in symtable.c
#define SYMBOL_TABLE_SIZE 1000

// 16 bit HACK addresses
typedef int16_t hack_addr;

/*
    Symbol - encapsulation of an HACK assembly symbol
    field1 - char *name - the symbol's name
    field2 - hack_addr addr - the 16 bit address
*/
typedef struct Symbol{
    char *name;
    hack_addr addr;
}Symbol;

//function prototypes

/*
    hash - hashes a Symbol's name field
    arg1 - char* str - the Symbol name to hash
    return - int - returns the hashed value 
*/
int hash(char *);

/*
    symtable_find - looks for a Symbol in the hashArray in symtable.c by its name
    arg1 - char *key - the name to use in order to find the symbol
    return - struct Symbol* - the Symbol if found, otherwise returns NULL
*/
struct Symbol *symtable_find(char*);

/*
    symtable_insert - inserts a Symbol into the hashArray in symtable.c with the field values
    arg1 - char* key - the name field of the Symbol
    arg2 - hack_addr - the addr - the address field of the Symbol
    return - void - returns nothing
*/
void symtable_insert(char*, hack_addr);

/*
    symtable_display_table - outputs all Symbols stored in the hashArray in symtable.c (empty/NULL positions are denoted as '~~')
    return - void - returns nothing
*/
void symtable_display_table();

/*
    symtable_print_labels - outputs the Symbols stored in the hashArray in symtable.c (empty/NULL positions are omitted)
    return - void - returns nothing
*/
void symtable_print_labels();
#endif