#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 2000

typedef struct code
{
	int op;
	int lvl;
	int mod;
	struct code * next;
} code;

void readFile(const char * fileName);
void pushCode(int comp[]);
void printCode();
char * getOp(int op);
void runProgram();
void executeLine();

code * codeStack;
int stack[MAX_STACK_SIZE];
int pc, bp, sp, halt;

int main(int argc, const char * argv[]) {
	
	const char * fileName = argv[1];

	readFile(fileName);

	printCode();

	runProgram();

	return 0;
}

void readFile(const char * fileName) {

	FILE * ifp;
	int i = 0, data;
	int comp[3];

	ifp = fopen(fileName, "r");

	if (ifp == NULL) {
		printf("Error: File not found\n");
		exit(0);
	}

	while(fscanf(ifp, "%d", &data) != EOF) {
		//printf("%d ", data);

		comp[i++ % 3] = data;

		if (i % 3 == 0 && i != 0) {
			//printf("\n");
			pushCode(comp);
		}
	}

	fclose(ifp);

	return;
}

void pushCode(int comp[]) {

	code * node = (code *) malloc(sizeof(code));
	code * last = codeStack;

	node -> op = comp[0];
	node -> lvl = comp[1];
	node -> mod = comp[2];
	node -> next = NULL;

	if (codeStack == NULL) {
		codeStack = node;
	} else {
		while (last -> next != NULL)
			last = last -> next;

		last -> next = node;
	}

	return;
}

void printCode() {

	code * current = codeStack;
	int i = 0;

	printf("PL/0 code:\n\n");

	while (current != NULL) {
		//printf("%d %d %d\n", current -> op, current -> lvl, current -> mod);
		printf(" %2d  %3s    %d    %2d\n", i++, getOp(current -> op), current -> lvl, current -> mod);
		current = current -> next;
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

void runProgram() {

	pc = 0;
	bp = 0;
	sp = 0;
	halt = 0;

	printf("\nExecution:\n");
	printf("                       pc   bp   sp   stack\n");

	while (halt == 0 && pc < MAX_STACK_SIZE) {
		executeLine();

		pc++;
	}

	return;
}

void executeLine() {



	return;
}