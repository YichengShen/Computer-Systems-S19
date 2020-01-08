#include <stdio.h>
#include <stdlib.h>
#include "gc.h"
#include "memorymgr.h"


void *stackBottom();
int *findBlock(int *ptr);
int *scanBlock(int *blockPtr);
void markBlock(int *ptr);
int isMarked(int *ptr);
void sweep(int **ptr, int **max);


void *stackBottom() {
	unsigned long bottom;
    FILE *statfp = fopen("/proc/self/stat", "r");
    fscanf(statfp,
           "%*d %*s %*c %*d %*d %*d %*d %*d %*u "
           "%*u %*u %*u %*u %*u %*u %*d %*d "
           "%*d %*d %*d %*d %*u %*u %*d "
           "%*u %*u %*u %lu", &bottom);
    fclose(statfp);
	return (void *) bottom;
}


void gc(){
	//printf("%lu\n", firstBlock());
	//printf("%lu\n", lastBlock());
	int **max = (int **)stackBottom(); //address of bottom
	int *dummy;
	int **ptr = &dummy; //address of top
	
	while (ptr <= max) {
		//check if the content of ptr is a pointer
		if (*ptr != 0) {
			// mark the block if reachable
			markBlock(*ptr);
		}
		ptr ++;
	}
	sweep(&dummy, max);
}


int *findBlock(int *ptr) {
	int *blockPtr = firstBlock();
	while (blockPtr != lastBlock()) {
		if (blockPtr <= ptr && ptr <= nextBlock(blockPtr)) return blockPtr;
		blockPtr = nextBlock(blockPtr);
	}
	return NULL;
}


int *scanBlock(int *blockPtr) {
	int *startPtr = blockPtr;
	//scan values in the block to see if it contains pointers to other blocks
	while (blockPtr != nextBlock(startPtr)) {
		if (*blockPtr != 0) {
			//mark the block if reachable
			markBlock(*blockPtr);
			}
		blockPtr++;
	}
	return 0;
}


void markBlock(int *ptr) {
	//check if this ptr is pointing to the heap
	if ( (firstBlock() <=  ptr) && (ptr <= lastBlock()) ) {
		int *blockPtr = findBlock(ptr);
		if (isAllocated(blockPtr)){
			*blockPtr = (*blockPtr) / 4 * 4 + 3;
		}
	scanBlock(blockPtr);
	}
}


int isMarked(int *p) {
	return (*p) % 4 == 3;
}


void sweep(int **ptr, int **max) {
	while (ptr <= max) {
		//check if the content of ptr is a pointer
		if (*ptr != 0) {
			//check if this ptr is pointing to the heap
			if ( (firstBlock() <=  *ptr) && (*ptr <= lastBlock()) ) {
				int *p = firstBlock();
				while (p != lastBlock()) {
					if (isMarked(p) == 0) {
						deallocate(p);
						}
					p = nextBlock(p);
				}
				coalesce();
			}
		}
		ptr ++;
	}
}
