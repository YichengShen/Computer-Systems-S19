#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void pushValStack (int stack[], int *top, int value);
int popValStack (int stack[], int *top);
void pushOpStack (char *stack[], int *top, char *value);
char *popOpStack (char *stack[], int *top);
int calculate (int stack[], int *top, char* op);


int main(int argc, char **argv) {
	int valStack[50];
	int valTop = -1;

	char *opStack[50];
	int opTop = -1;

	int i = 1;
	while (i < argc) {
		if (strcmp(argv[i], "+") == 0 || strcmp(argv[i], "x") == 0 || strcmp(argv[i], "[") == 0 ) {
			pushOpStack(opStack, &opTop, argv[i]);
		} 
		else if (strcmp(argv[i], "]") == 0) {
			while (1) {
				char* op0 = popOpStack(opStack, &opTop);
				while (strcmp(op0, "]") == 0) {
					op0 = popOpStack(opStack, &opTop);
				}
				if (strcmp(op0, "[") == 0) {break;}
				calculate(valStack, &valTop, op0);
			}
		} else {
			int val0 = atoi(argv[i]);
			pushValStack(valStack, &valTop, val0);
		}
		i++;
	}
	while (opTop != -1){
		char* op0 = popOpStack(opStack, &opTop);
		calculate(valStack, &valTop, op0);
	}
	printf("%d\n", popValStack(valStack, &valTop));
	return 0;
}


void pushValStack (int stack[], int *top, int value) {
	*top = *top + 1;
	stack[*top] = value;
}

int popValStack (int stack[], int *top){
	int temp = stack[*top];
	*top = *top - 1;
	return temp;
}


void pushOpStack (char *stack[], int *top, char *value){
	*top = *top + 1;
	stack[*top] = value;
}

char *popOpStack (char *stack[], int *top){
	char* temp = stack[*top];
	*top = *top - 1;
	return temp;
}

int calculate (int stack[], int *top, char* op){
	int val1 = popValStack(stack, top);
	int val2 = popValStack(stack, top);
	int result;
	if (strcmp(op, "+") == 0) {result = val1 + val2;}
	else {result = val1 * val2;}
	pushValStack(stack, top, result);
	}
