/****************************************
 * C-ploration 7 for CS 271
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

#define SYMBOL_TABLE_SIZE 1000

typedef int16_t hack_addr;

/*
Symbol - encapsulation of an assembly symbol
*/
typedef struct Symbol{
    char *name;
    hack_addr addr;

}Symbol;

//function prototypes
int hash(char *);
struct Symbol *symtable_find(char*);
void symtable_insert(char*, hack_addr);
void symtable_display_table();
void symtable_print_labels();