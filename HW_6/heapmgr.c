#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memorymgr.h"


int* first;
int* last;


void initmemory(int size){
	size += 12;
	size = multipleOf8(size);
	int *heap = (int *) malloc(size);
	first = heap;
	last = &heap[-1];
	//initialize the large free block
	heap[1] = size - 8;
	//initialize the sentinental block
	heap[-1] = 0;
}


void printallocation(){
	int *ptr = firstBlock()+1; // points to the header
	int i = 0;
	while (1) {
		if (*ptr == 0) break;
		else{
			
			if (isAllocated(ptr+1) == 1) {
				printf("Block %d: size %-2d\tallocated\n", i, *ptr-1);
			} else {
				printf("Block %d: size %-2d\tunallocated\n", i, *ptr);
			}
			ptr += (*ptr / sizeof(int));
			i++;
		}
	}
	printf("\n");
}


void *myalloc(int length){
	int *ptr = firstBlock()+2; //this pointer points to the start of payload
	length += 4;
	int size = multipleOf8(length);
	while (1) {
		int block_size = getHeaderVal(ptr);
		if (block_size == 0) return NULL;
		else if (isAllocated(ptr) != 1){
			if (block_size >= size) {
				*(ptr - 1) = size + 1;
				ptr += (size / sizeof(int));
				if (block_size > size) {
					*(ptr - 1) = block_size - size;
				}
				ptr -= (size / sizeof(int));
			return ptr;
			}
		} 
		ptr += (block_size / sizeof(int));
	}
}


void  myfree(void *ptr){
	int *header = (int*) ptr - 1;
	*header = (*header & -2);
}   


void  coalesce(){
	int *ptr = firstBlock()+2; //this pointer points to the start of payload
	while (1) {
		if (*(ptr - 1) == 0) break;
		else if (isAllocated(ptr) == 0) {
			int *startPtrHeader = ptr -1;
			ptr = nextBlock(ptr);
			while (1){
				if (*(ptr-1) == 0) break;
				if (isAllocated(ptr) == 0 ){
					*startPtrHeader += *(ptr - 1);
					ptr = nextBlock(ptr);
				}
			}
		}
		ptr = nextBlock(ptr);
	}
}   


//helper functions-------------------
int isAllocated(int *p){
	// p is the pointer to the payload
	if ( (*(p - 1) % 2) == 0 ) {return 0;}
	else {return 1;}
}
int *nextBlock(int *p){
	// p points to the payload
	return p + (*(p-1) / sizeof(int));
}
int *firstBlock(){
	return first;
}      
int *lastBlock(){
	return last;
}
int multipleOf8(int num){
	if ((num % 8) == 0) return num;
	return (num + 8 - (num%8));
}
int getHeaderVal(int *ptr){
	return *(ptr - 1);
}

