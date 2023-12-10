/****************************************
 * C-ploration 10 for CS 271
 * 
 * [NAME] Curtis Kauer
 * [TERM] FALL 2023
 * 
 * Implementation file for symtable.h
 ****************************************/
#include "symtable.h"

/*
    Symbol* hashArray - an Array of Symbol instances
    - Symbol index positions based on value returned from hash()
*/
Symbol* hashArray[SYMBOL_TABLE_SIZE];

/*
    hash - hashes a Symbol's name field
    arg1 - char* str - the Symbol name to hash
    return - int - returns the hashed value 
*/
int hash(char *str){
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % SYMBOL_TABLE_SIZE;    
}

/*
    symtable_insert - inserts a Symbol into the hashArray in symtable.c with the field values
    arg1 - char* key - the name field of the Symbol
    arg2 - hack_addr - the addr - the address field of the Symbol
    return - void - returns nothing
    - Allocates memory for the new Symbol instance, sizeof(Symbol)
    - Allocates memory for the name field of the Symbol instance, strlen(key) + 1
*/
void symtable_insert(char *key, hack_addr addr){
    Symbol *newSymbol = malloc(sizeof(Symbol));

    newSymbol->name = malloc(strlen(key) + 1);

    strcpy(newSymbol->name, key);
    newSymbol->addr = addr;

    int hashedKey = hash(key);

    while(hashArray[hashedKey] != NULL && hashArray[hashedKey]->name != NULL){
        hashedKey++;
        hashedKey %= SYMBOL_TABLE_SIZE;
    }

    hashArray[hashedKey] = newSymbol; 
}

/*
    symtable_find - looks for a Symbol in the hashArray in symtable.c by its name
    arg1 - char *key - the name to use in order to find the symbol
    return - struct Symbol* - the Symbol if found, otherwise returns NULL
*/
struct Symbol *symtable_find(char *key){
    int hashedKey = hash(key);

    while(hashArray[hashedKey] != NULL){
        if(strcmp(key, hashArray[hashedKey]->name) == 0){      
            return hashArray[hashedKey];
        }
        hashedKey++;
        hashedKey %= SYMBOL_TABLE_SIZE;
    }

    return NULL;
}

/*
    symtable_display_table - outputs all Symbols stored in the hashArray in symtable.c (empty/NULL positions are denoted as '~~')
    return - void - returns nothing
*/
void symtable_display_table(){
    for(unsigned index = 0; index < SYMBOL_TABLE_SIZE; index++){
        if(hashArray[index] != NULL){
            printf("(%s, %i)\n", hashArray[index]->name, hashArray[index]->addr);
        }
        else{
            printf(" ~~ \n");
        }
    }
}

/*
    symtable_print_labels - outputs the Symbols stored in the hashArray in symtable.c (empty/NULL positions are omitted)
    return - void - returns nothing
*/
void symtable_print_labels() {
   int i = 0;    
   for(i = 0; i<SYMBOL_TABLE_SIZE; i++) {
        if(hashArray[i] != NULL){
             printf("{%s,%d}\n",hashArray[i]->name,hashArray[i]->addr);
        }
   }
}