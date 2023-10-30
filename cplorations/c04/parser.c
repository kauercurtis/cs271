/****************************************
 * C-ploration 4 for CS 271
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

	while(fgets(line, sizeof(line), file)){
		
		strip(line);

		if(*line == '\0'){

			continue;

		}

		printf("%s\n", line);

	} 
	
}