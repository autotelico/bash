#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>

void runFind(char **args, int argSize) {
	DIR *dir;
	struct dirent *file;
	char *filename = args[1];
	dir = opendir(filename);	
	
	for (int i = 0; i < argSize; i++) {
		char *currentArg = args[i];
		if (strcmp(currentArg, "-name") == 0) {
			char *fileToFind = args[i + 1];
			if (fileToFind == NULL) {
				perror("No filename specified to search.");
			}
			
			while (file = readdir(dir)) {
				char *curFilename = file->d_name;
				if (strcmp(curFilename, fileToFind) == 0) {
					char fullPath [PATH_MAX + 1];
					char *ptr = realpath(curFilename, fullPath);
					printf("%s", ptr);
					return;
				}
			}
		}
	}

	while (file = readdir(dir)) {
		printf("%s\t", file->d_name);
	}
	printf("\n");

}

void runRm(char** filenames, int fileCount) {
	for (int i = 0; i < fileCount; i++) {
		int result = remove(filenames[i]);
		printf("%d\n", result);
	}
}

void runEcho(char** stringArray, int size) {
	for (int i = 1; i < size - 1; i++) {
		printf("%s ", stringArray[i]);
	}
	printf("\n");
}

void runLs(char* args[], int argsSize) {
	DIR* fd;
	struct dirent* in_file;
	fd = opendir(".");
	if (fd == NULL) {
		fprintf(stderr, "Error: failed to open directory");
		exit(1);
	}

	// if there are options
	int optAll = 0; // -a
	
	for (int i = 0; i < argsSize; i++) {
		if (strcmp(args[i], "-a") == 0) {
			optAll = 1;
			break;
		}
	}

	while ((in_file = readdir(fd))) {
		if (optAll == 0) {
			if (in_file->d_name[0] == '.') {
				continue;
			}
		}
		printf("%s\t", in_file->d_name);
	}
	printf("\n");

	closedir(fd);
}

void runCat(char* filename) {
	FILE *fptr;
	char content[100];
	fptr = fopen(filename, "r");
	while (fgets(content, 100, fptr)) {
		printf("%s", content);
	}
	fclose(fptr);
}

void parseCmd(char** cmd, int size) {
	// echo
	if (strcmp(cmd[0], "echo") == 0) {	
		runEcho(cmd, size);
	}
	
	// ls
	if (strcmp(cmd[0], "ls") == 0) {
		runLs(cmd, size - 1);
	}

	// cat
	if (strcmp(cmd[0], "cat") == 0) {
		runCat(cmd[1]);
	}

	// rm
	if (strcmp(cmd[0], "rm") == 0) {
		runRm(&cmd[1], size - 2);
	}

	if (strcmp(cmd[0], "find") == 0) {
		 runFind(cmd, size);
	}

}

void parseTokens(char text[]) {
}

int main(int argc, char** argv) {
	parseCmd(&argv[1], argc);
	
	return 0;
}

