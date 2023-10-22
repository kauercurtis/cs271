/****************************************
 * C-ploration 3 for CS 271
 * 
 * [NAME] Curtis Kauer
 * [TERM] FALL 2023
 * 
 ****************************************/
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>

#define MAX_LINE_LENGTH 200

int main(int argc, const char *argv[])
{	
	//printf("program starts\n");
	if(argc != 2){
		printf("Usage: %s [filename]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	//printf("opening file\n");
	FILE *fin = fopen(argv[1], "r");

	if(fin == NULL){
		perror("Unable to open file!");
		exit(EXIT_FAILURE);
	}

	//printf("declaring output file\n");
	char *out_file = malloc(sizeof(char) * 500000);

	//printf("copying to output file\n");

	strcpy(out_file, argv[1]);
	//printf("%s", out_file);
	//printf("stringcat\n");
	strcat(out_file, ".echo\0");
	
	//printf("%s", out_file);

	FILE *fout = fopen(out_file, "w+");

	//printf("initializing line string\n");
	char line[MAX_LINE_LENGTH] = {0};
	unsigned int line_num = 0;

	//printf("entering while loop\n");
	while(fgets(line, sizeof(line), fin)){
		line_num++;
		printf("[%04d] ", line_num);
		fprintf(fout, "[%04d]", line_num);
		printf("%s", line);
		fprintf(fout, line);
	} 

	fclose(fin);
	fclose(fout);
	free(out_file);
	out_file = 0;
	return 1;
}
