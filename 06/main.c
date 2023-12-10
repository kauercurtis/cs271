/****************************************
 * C-ploration 10 for CS 271
 * 
 * [NAME] Curtis Kauer
 * [TERM] FALL 2023
 * 
 * Main driving function for whole program
 ****************************************/
#include "parser.h"
#include "error.h"

// Maximum Number of HACK instructions to process
#define MAX_INSTRUCTION_COUNT 30000

/*
	main - Driving function for the whole program
	arg1 - int argc - the number of arguments given for arg2 (ommited during execution)
	arg2 - const char *argv[] - HACK Assembly file to process
	return - int - returns 0 upon successful execution

	- if argc is not exactly 2, program terminates with error (error.h)
	- if file is not opened correctly, program terminates with error (error.h)
	- Allocates memory for an Array of Instruction instances (parser.h), MAX_INSTRUCTION_COUNT * sizeof(Instruction)
	- Frees Array of Instruction instances before returning 0
*/
int main(int argc, const char *argv[])
{		

	if(argc != 2){
		exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
	}
	else if(strstr(argv[1], ".asm") == NULL){
		exit_program(EXIT_INVALID_FILE, argv[1]);
	}

	FILE *fin = fopen(argv[1], "r");

	if(fin == NULL){
		exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
	}	

	Instruction *instructions = (Instruction*)malloc(MAX_INSTRUCTION_COUNT * sizeof(Instruction));

	int num_instructions = parse(fin, instructions);

	fclose(fin);

	assemble(argv[1], instructions, num_instructions);

	free(instructions);

	return 0;		
}


