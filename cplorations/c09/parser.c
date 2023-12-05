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
void parse(FILE * file){
	
	Instruction instr;

	char inst_type; 
	int inst_num = 0;

	char line[MAX_LINE_LENGTH] = {0};
	char label[MAX_LABEL_LENGTH] = {0};

	int line_num = 0;

	add_predefined_symbols();

	while(fgets(line, sizeof(line), file)){
		line_num++;
		
		if(inst_num > MAX_INSTRUCTIONS){

			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);

		}

		strip(line);
		if(*line == '\0'){
			continue;
		}
		if(is_Atype(line)){
			inst_type = 'A';
			//if(!parse_A_instruction(line, &instr.instr.a))
			if (!parse_A_instruction(line, &instr.a_instruction)){
    			exit_program(EXIT_INVALID_A_INSTR, line_num, line);
 			}
 			//instr.instr_type = 0;
			instr.instr_type = A_TYPE_INSTRUCTION;
		}
		else if(is_label(line)){
			inst_type = 'L';
			extract_label(line, label);
			
			if(!isalpha(*label)){
				exit_program(EXIT_INVALID_LABEL, line_num, label);
			}
			else if(symtable_find(label) != NULL){
				exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, label);
			}
			
			strcpy(line, label);

			symtable_insert(label, inst_num);

			continue;
		}
		else if(is_Ctype(line)){
			inst_type = 'C';
		}

		//printf("%u: %c  %s\n", inst_num, inst_type, line);

		inst_num++;
	} 
	
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

	char *s = malloc(sizeof(line));

	strcpy(s, line + 1);

	char *s_end = NULL;

	long result = strtol(s, &s_end, 10);

	if(s == s_end){

		instr->label = malloc(sizeof(line));
		strcpy(instr->label, s);
		instr->is_addr = false;
	}
	else if(*s_end != 0){

		return false;

	}
	else{

		instr->address = result;
		instr->is_addr = true;

	}

	return true;

}