#include <stdio.h>
#include <stdlib.h>
#include "bst.h"



BSTnode *root = NULL;


struct wordcount {
	char word[80];
	int count;
};
typedef struct wordcount WordCount;


int compare_str(void *a, void* b);


int main() {
	char word[80];
	//int max = -1;
	BSTnode *max_node = NULL;
	while (scanf("%s", word) >= 0){
		
		if (word != NULL) {
			BSTnode *new = createNode(word);
			BSTnode *node_found = find(root, new, compare_str);
			if (node_found != NULL) {
				if (compare_str(((WordCount*)new->item)->word, ((WordCount*)node_found->item)->word) == 0) {
					((WordCount *)node_found->item)->count ++;
					if (max_node == NULL || ((WordCount *)node_found->item)->count > ((WordCount *)max_node->item)->count) {
						max_node = node_found;
					}
					
				}	
			}
			insert(root, new, compare_str);
			
		}
	}
	//printf("%s\t", ((WordCount*)root->right->left->item)->word);
	//find max -------
	int max = ((WordCount *)max_node->item)->count;
	char *max_word = ((WordCount *)max_node->item)->word;
	//--------------
	printf("The most frequent word is \"%s\", which appears %d times.\n", max_word, max);
	return 0;
}


int compare_str(void *a, void* b) {
	char *x = (char *)a;
	char *y = (char *)b;
	int r = strcmp(x, y);
	if (r < 0) {
		return -1;
	} 
	else if (r == 0) {
		return 0;
	} else {
		return 1;
	}
}
