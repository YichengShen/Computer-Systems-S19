#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"


extern BSTnode *root;


struct wordcount {
	char word[80];
	int count;
};
typedef struct wordcount WordCount;


BSTnode *createNode(void *item) {
	WordCount *newWord = (WordCount*)malloc(sizeof(WordCount));
	strcpy(newWord->word, (char*)item);
	newWord->count = 1;
	BSTnode* newNode = (BSTnode*)malloc(sizeof(BSTnode));
	newNode->item = (WordCount*)newWord;
	return newNode;
}

// Search the tree rooted at node n for the node matching the specified item.
// If the item exists, return its node.  If not, return the node that would be its parent.
// The function "compare" compares items.
BSTnode *find(BSTnode *n, void *item, int compare(void *, void *)) {
	BSTnode *new_node = (BSTnode *)item;
	if (n == NULL) return NULL;
	int cmp_result;
	BSTnode *currentNode = root;
	BSTnode *previousNode = NULL;
	while (currentNode != NULL) {
		previousNode = currentNode;
		cmp_result = compare(((WordCount*)new_node->item)->word, ((WordCount*)currentNode->item)->word);
		if (cmp_result < 0) 
			currentNode = currentNode->left;
		else if (cmp_result > 0) 
			currentNode = currentNode->right;
		else 
			return currentNode;
	//printf("%s\t", ((WordCount*)previousNode->item)->word);
	}
	return previousNode;
}

// Insert an item into the tree rooted at node n.
// If the tree already has a node for that item, do nothing.
void insert(BSTnode *n, void *item, int compare(void *, void *)) {
	BSTnode *node_insert = (BSTnode *)item;
	if (n == NULL) {
		root = node_insert;
	}
	else {
		int node_exists = 0;
		int is_leftchild = 0;
		int cmp_result = 0;
		BSTnode *current_node = root;
		BSTnode *previous_node = NULL;
		
		while (current_node != NULL) {
			cmp_result = compare(((WordCount*)node_insert->item)->word, ((WordCount*)current_node->item)->word);
			previous_node = current_node;
			if (cmp_result < 0) {
				node_exists = 0;
				is_leftchild = 1;
				current_node = current_node->left;
			}
			else if (cmp_result > 0) {
				node_exists = 0;
				is_leftchild = 0;
				current_node = current_node->right;
			} else {
				node_exists = 1;
				break;
			}
			// when cmp_result is 0 do nothing!!!!!!!!
		}
		if (node_exists != 1){
			if (is_leftchild) {
				previous_node->left = node_insert;
			} else{
				previous_node->right = node_insert;
			}
		}
	}
}


