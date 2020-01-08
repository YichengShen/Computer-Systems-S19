#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	int int_num;
	if (argc < 2) {
		int_num = 10;
	} else {
		int_num = atoi(argv[1]);
	}
	
	
	int *int_array = (int *)malloc(int_num*sizeof(int));
	int current_int;
	int count = 0;
	while (1) {
		int i = 0;
		scanf("%d", &current_int);
		if (current_int == -1) {break;}
		else {
			while (i < int_num) {
				int_array[i] = int_array[i+1];		
				i++;
			}
			int_array[int_num-1] = current_int;
			count += 1;
		}
	}
	int print_times;
	if (count < int_num) {
		printf("There are only %d numbers: ", count);
		print_times = count;
	}
	else {
		printf("Here are the last %d numbers: ", count);
		print_times = int_num;
	}
	int j = 0;
	while (j < print_times){
		printf("%d ", int_array[int_num - print_times + j]);
		j++;
	}
	printf("\n");
	free(int_array);
}



