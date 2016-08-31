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
	FILE * ofp;

	ifp = fopen(argv[1], "r");
	ofp = fopen(argv[2], "r");

	printf("Hello World!\n");

	fclose(ifp);
	fclose(ofp);

	return 0;
}