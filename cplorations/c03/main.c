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

	if(argc != 2){
		printf("Usage: %s [filename]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	FILE *fin = fopen(argv[1], "r");

	if(fin == NULL){
		perror("Unable to open file!");
		exit(EXIT_FAILURE);
	}

	char *out_file = malloc(sizeof(char) * 128);

	strcpy(out_file, argv[1]);
	strcat(out_file, ".echo\0");

	FILE *fout = fopen(out_file, "w+");

	char line[MAX_LINE_LENGTH] = {0};
	unsigned int line_num = 0;

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
