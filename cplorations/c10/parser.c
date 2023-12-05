/****************************************
 * C-ploration 8 for CS 271
 * 
 * [NAME] Curtis Kauer
 * [TERM] FALL 2023
 * 
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

	// instr.instruction_Type.a_instruction.is_addr = false;
	// instr.instruction_Type.a_instruction.aType.label = "if we see this means the label is wrong.";

	char inst_type; 
	int inst_num = 0;

	char line[MAX_LINE_LENGTH] = {0};
	//char label[MAX_LABEL_LENGTH] = "if we see this means the label is wrong.";{0};
	char tmp_line[MAX_LINE_LENGTH] = {0};

	int line_num = 0;

	add_predefined_symbols();

	while(fgets(line, sizeof(line), file) != NULL){
		printf("Line: %s\n", line);
		
		line_num++;
		
		//strcpy(tmp_line, line);

		if(inst_num > MAX_INSTRUCTIONS){

			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);

		}

		strip(line);
		strcpy(tmp_line, line);
		
		if(*line == '\0'){
			continue;
		}
		if(is_Atype(line)){
			printf("Start of A type\n");
			inst_type = 'A';
			//if(!parse_A_instruction(line, &instr.instr.a))
			if (!parse_A_instruction(line, &instr.instruction_Type.a_instruction)){
    			exit_program(EXIT_INVALID_A_INSTR, line_num, line);
 			}
 			instr.instr_type = A_TYPE_INSTRUCTION;
			//printf("Label = %s\n", instr.instruction_Type.a_instruction.aType.label);	
			//instructions[inst_num++] = instr;
			printf("A type\n");
		}
//		else if(is_label(line)){
		else if(is_label(line)){
			printf("Start of L type\n");
			inst_type = 'L';

			char label[MAX_LABEL_LENGTH] = {0};
			
			strcpy(line, extract_label(line, label));
			
			if(!isalpha(*label)){
				exit_program(EXIT_INVALID_LABEL, line_num, line);
			}
			else if(symtable_find(label) != NULL){
				exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
			}
			
			//strcpy(line, label);

			symtable_insert(label, inst_num);

			printf("Label type\n");

			continue;
		}
//		else if(is_Ctype(line)){
		else if(is_Ctype(line)){
			printf("Start of C type\n");
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
			//instructions[inst_num++] = instr;
			printf("C type\n");
		}

		//printf("%u: %c  %s\n", inst_num, inst_type, line);
		if(instr.instruction_Type.a_instruction.is_addr && instr.instr_type == A_TYPE_INSTRUCTION){

			printf("A: %d\n", instr.instruction_Type.a_instruction.aType.address);

		}
		else if(instr.instr_type == A_TYPE_INSTRUCTION){

			//printf("A: %d\n", label);
			printf("A: %s\n", instr.instruction_Type.a_instruction.aType.label);

		}
		//inst_num++;
		instructions[inst_num++] = instr;

		printf("line number: %d. Instruction Number: %d\n", line_num, inst_num);
	} 
	
	printf("line number: %d. Instruction Number: %d\n", line_num, inst_num);
	
	return inst_num;
}

/*
is_Atype - determines if a line is interacting with A register
param1 - const char *line - the line to determine
return - bool - if the line is A register type, return true, false if any other case
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
is_label - determines the given line is a identifier of a group
param1 - const char *line - line to determine
return - bool - if the line starts with ( and ends with ), return true, otherwise return false
*/
bool is_label(const char *line){
	unsigned length = strlen(line);
	if(*line == '(' && line[length - 1] == ')'){
		return true;
	}
	else{
		return false;
	}
}

/*
is_Ctype - determines if the the given line is a C instruction
param1 - const char *line - line to determine
return - bool - if the start of the line is NOT ( AND NOT @, return true, otherwise return false
*/
bool is_Ctype(const char *line){
	if(*line != '(' && *line != '@'){
		return true;
	}
	else{
		return false;
	}
}

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

void add_predefined_symbols(){

	for(unsigned index = 0; index < NUM_PREDEFINED_SYMBOLS; index++){

		predefined_symbol temp = predefined_symbols[index]; 

		symtable_insert(temp.name, temp.address);
	}

}

bool parse_A_instruction(const char *line, A_instruction *instr){

	printf("A parsing\n");

	char *s = NULL;

	s = malloc(strlen(line));

	strcpy(s, line + 1);

	char *s_end = NULL;

	long result = strtol(s, &s_end, 10);
	printf("strtol\n");

	printf("A parsing ready\n");

	if(s == s_end){

		instr->aType.label = (char*)malloc(strlen(line));
		strcpy(instr->aType.label, s);
		instr->is_addr = false;

		//printf("Label = %s\n", instr->aType.label);
	}
	else if(*s_end != 0){

		return false;

	}
	else{

		instr->aType.address = result;
		instr->is_addr = true;
	}

	return true;

}

void parse_C_instruction(char *line, C_instruction *instr){

	char *destinationAndComp = NULL;
	char *jump = NULL;
	char *comp = NULL;
	char *destination = NULL;

	destinationAndComp = strtok(line, ";");
	jump = strtok(NULL, ";");

	destination = strtok(destinationAndComp, "=");

	comp = strtok(NULL, "=");

	int foo = strchr(destination, 'M') != NULL ? 1 : 0;



	if(comp == NULL){

		//strcpy(comp, destination);
		instr->dest = str_to_destid(comp);
		instr->comp = str_to_compid(destination, &foo);
	}
	else{

		instr->dest = str_to_destid(destination);
		instr->comp = str_to_compid(comp, &foo);

	}

	//printf("Destination: %s\n", destination);
	//printf("Jump: %s\n", jump);
	//printf("Comp: %s\n", comp);


	instr->jump = str_to_jumpid(jump);
	//instr->dest = str_to_destid(destination);
	
	//int foo = strchr(destination, 'M') != NULL ? 1 : 0; 
	//instr->a = (signed char)foo;
	//instr->comp = str_to_compid(comp, &foo);
	//instr->comp = str_to_compid(comp, &foo);
	//instr->comp = str_to_compid(comp);
}