/****************************************
 * C-ploration 8 for CS 271
 * 
 * [NAME] Curtis Kauer
 * [TERM] FALL 2023
 * 
 ****************************************/
#include "symtable.h"

Symbol* hashArray[SYMBOL_TABLE_SIZE];

/*
hash - hashes a string
param1 - char *str - the string to hash
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
symtable_insert - inserts a symbol into hashArray
param1 - char *key - the position in the hashArray to add to
param2 - hack_addr addr - the address to add to hashArray
return - void - returns nothing
*/
void symtable_insert(char *key, hack_addr addr){

    Symbol *newSymbol = malloc(sizeof(Symbol));

    newSymbol->name = malloc(sizeof(key + 1));
    //strdup(key);
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
symtable_find - looks for a symbol in the hashArray
param1 - char *key - the key of the symbol being searched for
return - struct Symbol - the encapsulation of the symbol or returns NULL if not found
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
symtable_display_table - displays the hashArray's contents
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
symtable_print_labels - outputs the labels of the contents in hashArray
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