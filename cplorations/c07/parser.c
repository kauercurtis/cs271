/****************************************
 * C-ploration 5 for CS 271
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
	
	char line[MAX_LINE_LENGTH] = {0};
	char label[MAX_LABEL_LENGTH] = {0};
	unsigned lineNumber = 0;

	while(fgets(line, sizeof(line), file)){
		strip(line);
		if(*line == '\0'){
			continue;
		}
		if(is_Atype(line)){
			lineNumber++;
		}
		else if(is_label(line)){
			extract_label(line, label);
			strcpy(line, label);
			symtable_insert(label, lineNumber);
		}
		else if(is_Ctype(line)){
			lineNumber++;
		}
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

