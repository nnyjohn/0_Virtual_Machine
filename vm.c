#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct codeStack
{
	int op;
	int lvl;
	int mod;
	struct CodeStack * next;
} * code;

struct memStack
{
	int info;
	struct memStack * next;
} * stack;

int main(int argc, const char * argv[]) {
	
	char * fileIn;
	FILE * ifp;

	ifp = fopen(argv[1], "r");

	printf("Hello World!\n");

	fclose(ifp);

	return 0;
}