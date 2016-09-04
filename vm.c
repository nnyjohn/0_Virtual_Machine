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
int getOp(int op, int m, char * opCode);
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
	char * opCode = (char *) malloc(sizeof(char) * 3);

	printf("PL/0 code:\n\n");

	for (i = 0; i < size; i++)
		if (getOp(code[i].op, code[i].m, opCode))
			printf(" %2d  %3s    %d    %2d\n", i, opCode, code[i].l, code[i].m);
		else
			printf(" %2d  %3s         %2d\n", i, opCode, code[i].m);

	return;
}

int getOp(int op, int m, char * opCode) {

	int printL = 0;

	switch(op) {
		case 1:
			strcpy(opCode, "LIT");
			break;
		case 2:
			switch(m) {
				case 0:
					strcpy(opCode, "RET");
					break;
				case 1:
					strcpy(opCode, "NEG");
					break;
				case 2:
					strcpy(opCode, "ADD");
					break;
				case 3:
					strcpy(opCode, "SUB");
					break;
				case 4:
					strcpy(opCode, "MUL");
					break;
				case 5:
					strcpy(opCode, "DIV");
					break;
				case 6:
					strcpy(opCode, "ODD");
					break;
				case 7:
					strcpy(opCode, "MOD");
					break;
				case 8:
					strcpy(opCode, "EQL");
					break;
				case 9:
					strcpy(opCode, "NEQ");
					break;
				case 10:
					strcpy(opCode, "LSS");
					break;
				case 11:
					strcpy(opCode, "LEQ");
					break;
				case 12:
					strcpy(opCode, "GTR");
					break;
				case 13:
					strcpy(opCode, "GEQ");
					break;
				default:
					strcpy(opCode, "ER");
					break;
			}
			break;
		case 3:
			strcpy(opCode, "LOD");
			printL = 1;
			break;
		case 4:
			strcpy(opCode, "STO");
			printL = 1;
			break;
		case 5:
			strcpy(opCode, "CAL");
			printL = 1;
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

	return printL;
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
