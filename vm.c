#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_SIZE 512

struct codeStack
{
	int op;
	int lvl;
	int mod;
	struct codeStack * next;
} * code, * pc;

struct memStack
{
	int info;
	struct memStack * next;
} * stack;

void readFile(const char * fileName);
void pushCode(int comp[]);
void printCode();

int main(int argc, const char * argv[]) {
	
	const char * fileName = argv[1];

	readFile(fileName);

	printCode();

	return 0;
}

void readFile(const char * fileName) {

	FILE * ifp;
	char line[FILE_SIZE + 1], temp;
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

	struct codeStack * node = (struct codeStack *) malloc(sizeof(struct codeStack));
	struct codeStack * last = code;

	node -> op = comp[0];
	node -> lvl = comp[1];
	node -> mod = comp[2];
	node -> next = NULL;

	if (code == NULL) {
		code = node;
	} else {
		while (last -> next != NULL)
			last = last -> next;

		last -> next = node;
	}

	return;
}

void printCode() {

	struct codeStack * current = code;

	while (current != NULL) {
		printf("%d %d %d\n", current -> op, current -> lvl, current -> mod);
		current = current -> next;
	}
}