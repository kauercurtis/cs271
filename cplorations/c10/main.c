/****************************************
 * C-ploration 8 for CS 271
 * 
 * [NAME] Curtis Kauer
 * [TERM] FALL 2023
 * 
 ****************************************/
#include "parser.h"
#include "error.h"

#define MAX_INSTRUCTION_COUNT 30000

int main(int argc, const char *argv[])
{		

	if(argc != 2){
		exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
	}

	FILE *fin = fopen(argv[1], "r");

	if(fin == NULL){
		exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
	}	

	Instruction *instructions = (Instruction*)malloc(MAX_INSTRUCTION_COUNT * sizeof(Instruction));

	int num_instructions = parse(fin, instructions);

	//symtable_print_labels();
	printf("number of instructions: %i", num_instructions);

	fclose(fin);

	free(instructions);

	//symtable_display_table();

	return 0;		
}


