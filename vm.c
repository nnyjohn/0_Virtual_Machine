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

void initStack(int stack[]);
void readFile(const char * fileName, instruction code[]);
void printCode(int size, instruction code[]);
void printLine(instruction ir, int i);
void getOp(int op, int m, int * printL, int * printM, char * opCode);
void fetchCycle(instruction code[], int stack[], int * pc, int * bp, int * sp, int * ir);
void executeCycle(instruction ir, int stack[], int * pc, int * bp, int * sp, int * halt);
int base(int level, int b, int stack[]);
void printContents(instruction ir, int i, int pc, int bp, int sp, int stack[]);
void printStack(int stack[], int sp, int bp);

int main(int argc, const char * argv[]) {
	
	const char * fileName = argv[1];
	instruction code[MAX_CODE_LENGTH];
	int stack[MAX_STACK_HEIGHT];
	int * pc, * bp, * sp, * ir;

	initStack(stack);

	pc = (int *) malloc(sizeof(int));
	bp = (int *) malloc(sizeof(int));
	sp = (int *) malloc(sizeof(int));
	ir = (int *) malloc(sizeof(int));

	readFile(fileName, code);

	fetchCycle(code, stack, pc, bp, sp, ir);

	free(pc);
	free(bp);
	free(sp);
	free(ir);

	return 0;
}

void initStack(int stack[]) {

	int i;

	for (i = 0; i < MAX_STACK_HEIGHT; i++)
		stack[i] = 0;

	return;
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
		if (code[i].l > MAX_LEXI_LEVELS)
			code[i].l = MAX_LEXI_LEVELS;

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
		printLine(code[i], i);
		printf("\n");
	}

	return;
}

void printLine(instruction ir, int i) {

	int * printL = (int *) malloc(sizeof(int));
	int * printM = (int *) malloc(sizeof(int));
	char * opCode = (char *) malloc(sizeof(char) * 3);

	getOp(ir.op, ir.m, printL, printM, opCode);

	if (*printL)
		printf(" %2d  %3s   %2d   ", i, opCode, ir.l);
	else
		printf(" %2d  %3s        ", i, opCode);

	if (*printM)
		printf("%2d", ir.m);
	else
		printf("  ");

	free(printL);
	free(printM);
	free(opCode);

	return;
}

void getOp(int op, int m, int * printL, int * printM, char * opCode) {

	*printL = 0;
	*printM = 1;

	switch(op) {
		case 1:
			strcpy(opCode, "LIT");
			break;
		case 2: // OPR
			switch(m) {
				case 0:
					strcpy(opCode, "RET");
					*printM = 0;
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
			*printL = 1;
			break;
		case 4:
			strcpy(opCode, "STO");
			*printL = 1;
			break;
		case 5:
			strcpy(opCode, "CAL");
			*printL = 1;
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
		case 9: // SIO
			switch(m) {
				case 0:
					strcpy(opCode, "OUT");
					break;
				case 1:
					strcpy(opCode, "INP");
					break;
				case 2:
					strcpy(opCode, "HLT");
					*printM = 0;
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

	return;
}

void fetchCycle(instruction code[], int stack[], int * pc, int * bp, int * sp, int * ir) {

	int * halt;

	halt = (int *) malloc(sizeof(int));

	*pc = 0;
	*bp = 1;
	*sp = 0;
	*ir = 0;

	*halt = 0;

	printf("\nExecution:\n");
	printf("                      pc   bp   sp   stack\n");
	printf("                      %2d   %2d   %2d\n", *pc, *bp, *sp);

	while (*halt != 1 && *pc < MAX_CODE_LENGTH) {
		*ir = *pc;
		(*pc)++;
		
		executeCycle(code[*ir], stack, pc, bp, sp, halt);

		printContents(code[*ir], *ir, *pc, *bp, *sp, stack);
	}

	free(halt);

	return;
}

void executeCycle(instruction ir, int stack[], int * pc, int * bp, int * sp, int * halt) {

	switch(ir.op) {
		case 1: // LIT
			(*sp)++;
			stack[*sp - 1] = ir.m;
			break;
		case 2: // OPR
			switch(ir.m) {
				case 0: // RET
					*sp = *bp - 1;
					*pc = stack[*sp + 3];
					*bp = stack[*sp + 2];
					break;
				case 1: // NEG
					stack[*sp - 1] = -stack[*sp - 1];
					break;
				case 2: // ADD
					(*sp)--;
					stack[*sp - 1] = stack[*sp - 1] + stack[*sp];
					break;
				case 3: // SUB
					(*sp)--;
					stack[*sp - 1] = stack[*sp - 1] - stack[*sp];
					break;
				case 4: // MUL
					(*sp)--;
					stack[*sp - 1] = stack[*sp - 1] * stack[*sp];
					break;
				case 5: // DIV
					(*sp)--;
					stack[*sp - 1] = stack[*sp - 1] / stack[*sp];
					break;
				case 6: // ODD
					stack[*sp - 1] = stack[*sp - 1] % 2;
					break;
				case 7: // MOD
					(*sp)--;
					stack[*sp - 1] = stack[*sp - 1] % stack[*sp];
					break;
				case 8: // EQL
					(*sp)--;
					stack[*sp - 1] = stack[*sp - 1] == stack[*sp];
					break;
				case 9: // NEQ
					(*sp)--;
					stack[*sp - 1] = stack[*sp - 1] != stack[*sp];
					break;
				case 10: // LSS
					(*sp)--;
					stack[*sp - 1] = stack[*sp - 1] < stack[*sp];
					break;
				case 11: // LEQ
					(*sp)--;
					stack[*sp - 1] = stack[*sp - 1] <= stack[*sp];
					break;
				case 12: // GTR
					(*sp)--;
					stack[*sp - 1] = stack[*sp - 1] > stack[*sp];
					break;
				case 13: // GEQ
					(*sp)--;
					stack[*sp - 1] = stack[*sp - 1] >= stack[*sp];
					break;
				default:
					break;
			}
			break;
		case 3: // LOD
			(*sp)++;
			stack[*sp - 1] = stack[base(ir.l, *bp, stack) + ir.m];
			break;
		case 4: // STO
			stack[base(ir.l, *bp, stack) + ir.m - 1] = stack[*sp - 1];
			(*sp)--;
			break;
		case 5: // CAL
			stack[*sp] = 0;
			stack[*sp + 1] = base(ir.l, *bp, stack);
			stack[*sp + 2] = *bp;
			stack[*sp + 3] = *pc;
			*bp = *sp + 1;
			*pc = ir.m;
			break;
		case 6: // INC
			*sp = *sp + ir.m;
			break;
		case 7: // JMP
			*pc = ir.m;
			break;
		case 8: // JPC
			if (stack[*sp - 1] == 0) {
				*pc = ir.m;
			}
			(*sp)--;
			break;
		case 9: // SIO
			switch(ir.m) {
				case 0: // OUT
					printStack(stack, *sp, *bp);
					break;
				case 1: // INP
					(*sp)++;
					printf("Input: ");
					scanf("%d", &stack[*sp - 1]);
					break;
				case 2: // HLT
						*halt = 1;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

	return;
}

int base(int level, int b, int stack[]) {

	while (level > 0) {
		b = stack[b + 1];
		level--;
	}

	return b;
}

void printContents(instruction ir, int i, int pc, int bp, int sp, int stack[]) {

	printLine(ir, i);
	printf("    %2d   %2d   %2d   ", pc, bp, sp);
	printStack(stack, sp, bp);
	printf("\n");

	return;
}

void printStack(int stack[], int sp, int bp) {

	int i;

	for (i = 0; i < sp; i++) {
		if (bp - 1 == i && bp > 1)
			printf("| ");

		printf("%d ", stack[i]);
	}

	return;
}
