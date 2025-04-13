#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 1024L * 1024 * 1024 // 1 GB

int main(void) {
	int * allocedMem = (int*) malloc(SIZE);
	if (!allocedMem) {
		perror("Memory allocation failed");
		exit(1);
	}
	sleep(5);
	free(allocedMem);
	return 0;
}
