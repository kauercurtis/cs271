/****************************************
 * C-ploration 2 for CS 271
 * 
 * [NAME] Curtis Kauer
 * [TERM] FALL 2023
 * 
 ****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LIMIT 200  /* max size for static string */


/* Function: length
 * -------------
 * find the length of a char* string from scratch
 *   note: do not use strlen() library function!
 *
 * txt: the string (character array)
 *
 * returns: the length of the string
 */
int length(char* txt) {
	int len = 0;
	
	for(; txt[len] != '\0'; len++){}
	
	return len;  
}


/* Function: welcome
 * -------------
 * concatenates a welcome message together
 *   - add hello variable
 *   - add a single space (between words)
 *   - add user provided name
 *   - add a single exclamation point
 *
 * hello: string containing "hello"
 * name: string containing the name
 *
 * returns: "Hello NAME!", based on a given NAME 
 */
char *welcome(char* hello, char* name) {
	// dynamically allocate a new string
	char *message = malloc(sizeof(char)*MAX_LIMIT);
		
	message = strcat(message, hello);
	
	if(hello[strlen(hello) - 1] != ' ' && name[0] != ' '){

		strcat(message, " ");

	}

	strcat(message, name);
	strcat(message, "!");
	
	return message;	
}


/* Function: reverse
 * -------------
 * reverses a string
 *   note: we are using "pass-by-pointer" to save result
 *
 * txt: string to reverse
 * result: empty string in which to store result
 *
 * returns: nothing. result contains the reversed string.
 */
void reverse(char* txt, char* result) {

	unsigned txtLength = length(txt);
	int resultIndex = 0;
	
	for(int txtIndex = txtLength - 1; txtIndex >= 0; txtIndex--){

		*(result + resultIndex) = *(txt + txtIndex);
		resultIndex++;
	}

	*(result + txtLength) = '\0';
	
}


/* Function: vowels
 * -------------
 * count the number of vowels in the string
 *   - a, e, i, o, or u
 *
 * txt: string in which to count vowels
 *
 * returns: integer count of vowels
 */
int vowels(char* txt) {
	int vowels = 0;
	int currentIndex = 0;

	while(*(txt + currentIndex) != '\0'){

		if(*(txt + currentIndex) == 'a' || *(txt + currentIndex) == 'A'){

			vowels++;

		}
		else if(*(txt + currentIndex) == 'e' || *(txt + currentIndex) == 'E'){

			vowels++;

		}
		else if(*(txt + currentIndex) == 'i' || *(txt + currentIndex) == 'I'){

			vowels++;

		}
		else if(*(txt + currentIndex) == 'o' || *(txt + currentIndex) == 'O'){

			vowels++;

		}
		else if(*(txt + currentIndex) == 'u' || *(txt + currentIndex) == 'U'){

			vowels++;

		}
		
		currentIndex++;

	}

	return vowels;
}

/* Function: quartile
 * -------------
 * determines which quarter of the alphabet we find the name
 *   - A-F => 1
 *   - G-L => 2
 *   - M-R => 3
 *   - S-Z => 4
 *
 * Use the strcmp method from string.h
 *
 * name: string to check place in alphabet
 *
 * returns: integer quarter [1..4]
 */
int quartile(char* name) {

	if(strcmp(name, "G") < 0){

		return 1;

	}
	else if(strcmp(name, "M") < 0){

		return 2;
		
	}
	else if(strcmp(name, "T") < 0){
		return 3;
	}
	else{

		return 4;
		
	}
	
}


/* Function: main
 * -------------
 * parses command line arguments and executes appropriate function.
 *
 * =========================
 * DO NOT EDIT MAIN FUNCTION
 * =========================
 * 
 * argc: number of arguments
 * argv: array of arguments (array of array of chars)
 *
 * returns: 0 if no errors, 1 otherwise.
 */
int main(int argc, char** argv)
{
	// declare a string with value
	char hello[] = "Hello";
	// declare an empty string of max size
	char name[MAX_LIMIT];
	
	// prompt user for name
	printf("What is your name? ");
	// the [^\n] means to discard the newline character
	scanf("%[^\n]s", name);  
	// make sure name starts with a capital letter
	name[0] = toupper((unsigned char)name[0]);
	
	// when no arguments given
	if (argc < 2){
		// Task 1: display welcome
		char *greeting = welcome(hello, name);
		printf("%s\n", greeting);

		// Task 2: count characters 
		int len = length(name);
		printf("%s is %d characters long.\n", name, len);
		
		// Task 3: reverse string
		char backwards[length(name)]; 
		reverse(name, backwards);
		printf("%s backwards is %s.\n", name, backwards);
		
		// Task 4: count vowels
		printf("%s contains %d vowels.\n", name, vowels(name));	
		
		// Task 5: find which quarter of the alphabet
		printf("%s is in quartile #%d alphabetically.", name, quartile(name));		
	}else{
		/******************************
		 *  USED BY GRADESCOPE TESTS  *
		 *****************************/
		if (!strcmp(argv[1], "-count")){ 
			printf("%d\n", length(name));
		}else if (!strcmp(argv[1], "-greeting")){ 
			printf("%s\n", welcome(hello, name));			
		}else if (!strcmp(argv[1], "-reverse")){ 
			char backwards[length(name)]; 
			reverse(name, backwards);
			printf("%s\n", backwards);
		}else if (!strcmp(argv[1], "-vowel")){ 
			printf("%d\n", vowels(name));				
		}else if (!strcmp(argv[1], "-quartile")){ 
			printf("%d\n", quartile(name));			
		}else{
			// incorrect command, exit with error
			fprintf(stderr, "[error] Unknown command %s.\n", argv[1]);
			return 1;
		}		
	}
    return 0;
}