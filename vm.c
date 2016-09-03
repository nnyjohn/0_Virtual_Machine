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

void readFile(const char * fileName);
//void pushCode(int comp[]);
void printCode();
char * getOp(int op);
void fetchCycle();
void executeCycle();

instruction code[MAX_CODE_LENGTH];
int stack[MAX_STACK_HEIGHT];
int pc, bp, sp, ir;

int main(int argc, const char * argv[]) {
	
	const char * fileName = argv[1];

	readFile(fileName);

	printCode();

	fetchCycle();

	return 0;
}

void readFile(const char * fileName) {

	FILE * ifp;
	pc = 0;

	ifp = fopen(fileName, "r");

	if (ifp == NULL) {
		printf("Error: File not found\n");
		exit(0);
	}

	while(fscanf(ifp, "%d %d %d", &code[pc].op, &code[pc].l, &code[pc].m) != EOF) {

		pc++;
	}

	fclose(ifp);

	return;
}

void printCode() {

	int i;

	printf("PL/0 code:\n\n");

	for (i = 0; i < pc; i++) {
		printf(" %2d  %3s    %d    %2d\n", i, getOp(code[i].op), code[i].l, code[i].m);
	}

	return;
}

/*
 * Finish adding op codes
 */
char * getOp(int op) {

	char * opCode = (char *) malloc(sizeof(char) * 3);

	switch(op) {
		case 1:
			strcpy(opCode, "LIT");
			break;
		case 2:
			strcpy(opCode, "RET");
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
		case 9:
			strcpy(opCode, "HLT");
			break;
		default:
			strcpy(opCode, "ER");
			break;
	}

	return opCode;
}

void fetchCycle() {

	pc = 0;
	bp = 1;
	sp = 0;
	ir = 0;

	printf("\nExecution:\n");
	printf("                       pc   bp   sp   stack\n");
	printf("                        %d    %d    %d\n", pc, bp, sp);

	while (pc < MAX_STACK_HEIGHT) {
		executeCycle();

		pc++;
	}

	return;
}

void executeCycle() {



	return;
}
