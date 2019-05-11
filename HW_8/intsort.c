#include <stdio.h>
#include <stdlib.h>
#include "intsort.h"


// the head of the linked list
IntNode *first = NULL;


int main(int argc, char **argv) {
	printf("Enter some numbers, ending with -1: ");
	int current_int;
	while (1) {
		scanf("%d", &current_int);
		if (current_int == -1) {break;}
		else {
			insert(first, current_int);
		}
	}
	printAll(first);
}	


// create a node
IntNode *createNode(int val) {
	IntNode *new_node = (IntNode*)malloc(sizeof(IntNode));
	new_node->item = val;
	return new_node;
}

// insert a node into the chain, in sorted order
void insert(IntNode *header, int val) {
	IntNode *newNode = createNode(val);
	// when first is NULL or when the number is smaller than first
	if (header == NULL || val < header->item) {
		newNode->next = first;
		first = newNode;
	} else {
		IntNode *currentNode = first;
		while (currentNode->next != NULL && currentNode->next->item < val) {
			currentNode = currentNode->next;
		}
		newNode->next = currentNode->next;
		currentNode->next = newNode;
	}
}


// print the values stored in the chain of nodes
void printAll(IntNode *header) {
	IntNode *currentNode = header;
	while (currentNode != NULL){
		printf("%d ", currentNode->item);
		currentNode = currentNode->next;
	}
	printf("\n");
}

