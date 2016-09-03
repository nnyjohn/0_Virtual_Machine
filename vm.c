#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STACK_HEIGHT 2000
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 3

typedef struct instruction
{
	int op;
	int l;
	int m;
} instruction;

void readFile(const char * fileName, instruction code[]);
void printCode(int size, instruction code[]);
char * getOp(int op, int m);
void fetchCycle(instruction code[], int stack[], int * pc, int * bp, int * sp, int * ir);
void executeCycle(instruction ir);

int main(int argc, const char * argv[]) {
	
	const char * fileName = argv[1];
	instruction code[MAX_CODE_LENGTH];
	int stack[MAX_STACK_HEIGHT];
	int * pc, * bp, * sp, * ir;

	pc = (int *) malloc(sizeof(int));
	bp = (int *) malloc(sizeof(int));
	sp = (int *) malloc(sizeof(int));
	ir = (int *) malloc(sizeof(int));

	readFile(fileName, code);

	fetchCycle(code, stack, pc, bp, sp, ir);

	return 0;
}

void readFile(const char * fileName, instruction code[]) {

	FILE * ifp;
	int i = 0;

	ifp = fopen(fileName, "r");

	if (ifp == NULL) {
		printf("Error: File not found\n");
		exit(0);
	}

	while(fscanf(ifp, "%d %d %d", &code[i].op, &code[i].l, &code[i].m) != EOF) {

		i++;
	}

	fclose(ifp);

	printCode(i, code);

	return;
}

void printCode(int size, instruction code[]) {

	int i;

	printf("PL/0 code:\n\n");

	for (i = 0; i < size; i++) {
		printf(" %2d  %3s    %d    %2d\n", i, getOp(code[i].op, code[i].m), code[i].l, code[i].m);
	}

	return;
}

/*
 * Finish adding op codes
 */
char * getOp(int op, int m) {

	char * opCode = (char *) malloc(sizeof(char) * 3);

	switch(op) {
		case 1:
			strcpy(opCode, "LIT");
			break;
		case 2:
			strcpy(opCode, "RET");
			break;
		case 3:
			strcpy(opCode, "LOD");
			break;
		case 4:
			strcpy(opCode, "STO");
			break;
		case 5:
			strcpy(opCode, "CAL");
			break;
		case 6:
			strcpy(opCode, "INC");
			break;
		case 7:
			strcpy(opCode, "JMP");
			break;
		case 8:
			strcpy(opCode, "JPC");
			break;
		case 9:
			switch(m) {
				case 0:
					strcpy(opCode, "OUT");
					break;
				case 1:
					strcpy(opCode, "INP");
					break;
				case 2:
					strcpy(opCode, "HLT");
					break;
				default:
					strcpy(opCode, "ER");
					break;
			}
			break;
		default:
			strcpy(opCode, "ER");
			break;
	}

	return opCode;
}

void fetchCycle(instruction code[], int stack[], int * pc, int * bp, int * sp, int * ir) {

	*pc = 0;
	*bp = 1;
	*sp = 0;
	*ir = 0;

	printf("\nExecution:\n");
	printf("                       pc   bp   sp   stack\n");
	printf("                        %d    %d    %d\n", *pc, *bp, *sp);

	while (*pc < MAX_CODE_LENGTH) {
		*ir = *pc;
		(*pc)++;
		
		executeCycle(code[*ir]);
	}

	return;
}

void executeCycle(instruction ir) {



	return;
}
