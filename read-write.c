#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeToFile(char *filename, char *newText) {
	FILE *file = fopen(filename, "w+");
	fputs(newText, file);
	fclose(file);
}

void readFile(char *filename) {
	FILE *file = fopen(filename, "r");
	char content[100];
	while (fgets(content, 100, file)) {
		printf("%s", content);
	}
	fclose(file);
}

int main(int argc, char **argv) {
	char *command = argv[1];

	if (strcmp(command, "write") == 0) {
		char *filename = argv[2];
		char *textToWrite = argv[3];
		writeToFile(filename, textToWrite);
	}

	if (strcmp(command, "read") == 0) {
		char *filename = argv[2];
		readFile(filename);
	}

	return 0;
}
