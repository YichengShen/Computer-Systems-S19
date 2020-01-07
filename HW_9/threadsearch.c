#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

int searchPosition(int i);
void *threadSearch(void *);

#define TEXT_LEN 1000000
#define NUM_THREADS 10

// The pattern and text strings are global variables
char *pattern;
char text[TEXT_LEN];

// Global variables for the threads
int location = 0;
int result = -1; 

//the lock
pthread_mutex_t locationLock;

int main(int argc, char *argv[]) {

   // Step 1: Extract the pattern string from the command line.   
   
   pattern = argv[1];
   int patlen = strlen(pattern);

   // Step 2: Create and populate the text string.

   int textlen = TEXT_LEN; // will be overridden by the actual length
   int count = 0;
   while (count < TEXT_LEN) {
       int status = scanf("%c", &text[count]);
       count++;
       if (status == EOF) {
          textlen = count;
          break;
       }
   }

   // Step 3: Search for the pattern in the text string

   // Create the threads for searching
   int thread_i = 0;
   pthread_t tid[NUM_THREADS];
  
   pthread_mutex_init(&locationLock, NULL);

   while (thread_i < NUM_THREADS) {
	pthread_create(&tid[thread_i], NULL, threadSearch, &textlen);
   	thread_i++;
   }
   int thread_j = 0;
   while (thread_j < NUM_THREADS) {
	pthread_join(tid[thread_j], NULL);
   	thread_j++;
   }
 

   // Step 4: Determine the result and print it

   if (result == -1)
       printf("Pattern not found\n");
   else
       printf("Pattern begins at character %d\n", result);
}


void *threadSearch(void *arg) {
	while (result == -1) {
		// get the starting location, and update the location by 1
		pthread_mutex_lock(&locationLock);
		int pos = location;
		int count = *(int *)arg;
		if (location < count) location ++;
		pthread_mutex_unlock(&locationLock);
		
		// start checking from that location
		if (searchPosition(pos) == 1) {
			pthread_mutex_lock(&locationLock);
          		result = pos; 
			pthread_mutex_unlock(&locationLock);
			break;
       		}
		if (location == count) break;
	}
	return NULL;
}


int searchPosition(int i) {
   int j;
   for (j=0;j<strlen(pattern); j++) 
       if (text[i+j] != pattern[j])
          return 0;
   return 1;
}
			
