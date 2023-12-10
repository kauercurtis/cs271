/****************************************
 * C-ploration 10 for CS 271
 * 
 * [NAME] Curtis Kauer
 * [TERM] FALL 2023
 * 
 * Implementation file for parser.h
 ****************************************/
#include "parser.h"

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s){	
	char s_new[strlen(s) + 1];
	unsigned indexCounter = 0;
	for(char *s2 = s; *s2; s2++){
		if(*(s2 + 0) == '/' && *(s2 + 1) == '/'){
			break;
		}
		else if(!isspace(*(s2))){
			s_new[indexCounter++] = *s2;
		}
	}

	s_new[indexCounter] = '\0';

	strcpy(s, s_new);

    return s;	
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
int parse(FILE * file, Instruction *instructions){
	Instruction instr;

	char inst_type; 
	int inst_num = 0;

	char line[MAX_LINE_LENGTH] = {0};
	char tmp_line[MAX_LINE_LENGTH] = {0};

	int line_num = 0;

	add_predefined_symbols();

	while(fgets(line, sizeof(line), file) != NULL){
		line_num++;

		if(inst_num > MAX_INSTRUCTIONS){
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
		}

		strip(line);
		
		if(!*line){
			continue;
		}
		if(is_Atype(line)){
			inst_type = 'A';

			if (!parse_A_instruction(line, &instr.instruction_Type.a_instruction)){
    			exit_program(EXIT_INVALID_A_INSTR, line_num, line);
 			}
 			instr.instr_type = A_TYPE_INSTRUCTION;
		}
		else if(is_label(line)){
			inst_type = 'L';

			char label[MAX_LABEL_LENGTH] = {0};
			
			strcpy(line, extract_label(line, label));
			
			if(!isalpha(*label)){
				exit_program(EXIT_INVALID_LABEL, line_num, line);
			}
			else if(symtable_find(label) != NULL){
				exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
			}

			symtable_insert(label, inst_num);

			continue;
		}
		else if(is_Ctype(line)){
			strcpy(tmp_line, line);
			inst_type = 'C';
			parse_C_instruction(tmp_line, &instr.instruction_Type.c_instruction);
			
			if(instr.instruction_Type.c_instruction.comp == COMP_INVALID){
				exit_program(EXIT_INVALID_C_COMP, line_num, line);
			}
			else if(instr.instruction_Type.c_instruction.dest == DEST_INVALID){
				exit_program(EXIT_INVALID_C_DEST, line_num, line);
			}
			else if(instr.instruction_Type.c_instruction.jump == JMP_INVALID){
				exit_program(EXIT_INVALID_C_JUMP, line_num, line);
			}
		
			instr.instr_type = C_TYPE_INSTRUCTION;

			printf("C: d=%d, c=%d, j=%d\n", instr.instruction_Type.c_instruction.dest, instr.instruction_Type.c_instruction.comp, instr.instruction_Type.c_instruction.jump);
		}

		if(instr.instruction_Type.a_instruction.is_addr && instr.instr_type == A_TYPE_INSTRUCTION){
			printf("A: %d\n", instr.instruction_Type.a_instruction.aType.address);
		}
		else if(instr.instr_type == A_TYPE_INSTRUCTION){
			printf("A: %s\n", instr.instruction_Type.a_instruction.aType.label);
		}

		instructions[inst_num++] = instr;
	} 
	
	return inst_num;
}

/*
    is_Atype - checks if a line is of A instruction type
    arg1 - const char* - the line to check
    return - bool - true if line is A instruction type, and false all other cases
*/
bool is_Atype(const char *line){
	if(*line == '@'){
		return true;
	}
	else{
		return false;
	}
}

/*
    is_label - checks if a line is a label
    arg1 - the line to check
    return - bool - true if line is a label and false all other cases
*/
bool is_label(const char *line){
	unsigned int length = strlen(line);
	if(*line == '(' && line[length - 1] == ')'){
		return true;
	}
	else{
		return false;
	}
}

/*
    is_Ctype - checks if a line is of C instruction type
    arg1 - the line to check 
    return - bool - true if the line is C instruction type, and false all other cases
*/
bool is_Ctype(const char *line){
	if(*line != '(' && *line != '@'){
		return true;
	}
	else{
		return false;
	}
}

/*
    extract_label - extracts the label name from a label line 
    arg1 - const char* line - the line to extract the label from
    arg2 - char* label - the string to hold the label name
    return - char* - the label name that is extracted
*/
char *extract_label(const char *line, char* label){
	unsigned currentIndex = 1;
	char currentCharacter = *(line + currentIndex);

	while(currentCharacter != ')'){
		label[currentIndex - 1] = currentCharacter;
		currentIndex++;
		currentCharacter = line[currentIndex];
	}

	label[currentIndex - 1] =  '\0';
	return label;
}

/*
    add_predefined_symbols - adds all 23 predefined HACK assembly symbols to hackArray in symtable.c
    return - void - returns nothing
*/
void add_predefined_symbols(){
	for(unsigned index = 0; index < NUM_PREDEFINED_SYMBOLS; index++){
		predefined_symbol temp = predefined_symbols[index]; 
		symtable_insert(temp.name, temp.address);
	}
}

/*
    parse_A_instruction - parses an HACK assembly A type instruction for assembling
    arg1 - const char *line - the line to parse
    arg2 - A_instruction *instr - the A instruction instance to store the instruction after parsing
    return - bool - true if successfully parsed and false all other cases
*/
bool parse_A_instruction(const char *line, A_instruction *instr){
	char *s = (char *)malloc(strlen(line));
	strcpy(s, line + 1);
	char *s_end = NULL;
	long result = strtol(s, &s_end, 10);

	if(s == s_end){
		instr->aType.label = (char*)malloc(strlen(line));
		strcpy(instr->aType.label, s);
		instr->is_addr = false;
	}
	else if(*s_end != 0){
		return false;
	}
	else{
		instr->aType.address = result;
		instr->is_addr = true;
	}

	free(s);
	return true;
}

/*
    parse_C_instruction - parses an HACK assembly C type instruction for assembling
    arg1 - char *line - the line to parse
    arg2 - C_instruction *instr - the C instruction instance to store the isntruction after parsing
    return - void - returns nothing
*/
void parse_C_instruction(char *line, C_instruction *instr){
	char *destinationAndComp = NULL;
	char *jump = NULL;
	char *comp = NULL;
	char *destination = NULL;

	destinationAndComp = strtok(line, ";");
	jump = strtok(NULL, ";");
	destination = strtok(destinationAndComp, "=");
	comp = strtok(NULL, "=");

	int a = 0;	

	if(comp == NULL){
		instr->dest = str_to_destid(comp);
		instr->comp = str_to_compid(destination, &a);
	}
	else{
		instr->dest = str_to_destid(destination);
		instr->comp = str_to_compid(comp, &a);
	}

	instr->jump = str_to_jumpid(jump);
	instr->a = a;
}

/*
    instruction_to_opcode - converts C instruction to opcode
    arg1 - C_instruction instr - the C instruction instance
    return - opcode - the 16 bit operation code
*/
opcode instruction_to_opcode(C_instruction instr){
	opcode op = 0;
	op |= (7 << 13);
	op |= (instr.a << 12);
	op |= (instr.comp << 6);
	op |= (instr.dest << 3);
	op |= (instr.jump << 0);	
	return op;
}

/*
    assemble - assembles a collection of instructions into binary
    arg1 - const char * file_name - the name of the HACK assembly file
    arg2 - Instruction *instructions - an array of Instruction Instances
    arg3 - int num_instructions - the number of Instructions in the instructions array (arg2)
    return - void - returns nothing
    - Creates a .hack file of the HACK assembly file
*/
void assemble(const char * file_name, Instruction* instructions, int num_instructions){
	char hackFile[sizeof(file_name) + 6];
	strcpy(hackFile, file_name);
	strcat(hackFile, ".hack");

	FILE *fin = fopen(hackFile, "w");

	if(fin == NULL){
		exit_program(EXIT_CANNOT_OPEN_FILE, hackFile);
	}

	int16_t op_code;
	int16_t address = 16; 

	for(unsigned currentInstruction = 0; currentInstruction < num_instructions; currentInstruction++){
		if(instructions[currentInstruction].instr_type == A_TYPE_INSTRUCTION){

			if(!instructions[currentInstruction].instruction_Type.a_instruction.is_addr){
				Symbol *symbol = symtable_find(instructions[currentInstruction].instruction_Type.a_instruction.aType.label);

				if(symbol == NULL){					
					op_code = address;
					symtable_insert(instructions[currentInstruction].instruction_Type.a_instruction.aType.label, address);
					address++;
				}
				else{
					op_code = symbol->addr;
				}
			}
			else{
				op_code = instructions[currentInstruction].instruction_Type.a_instruction.aType.address;
			}
		}
		else{
			op_code = instruction_to_opcode(instructions[currentInstruction].instruction_Type.c_instruction);
		}

		fprintf(fin, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", OPCODE_TO_BINARY(op_code));
	}

	fclose(fin);
}