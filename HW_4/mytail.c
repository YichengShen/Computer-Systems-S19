#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char * readaline(int max);


int main(int argc, char **argv) {
	int line_num;
	if (argc < 2) {
		line_num = 10;
	} else {
		line_num = atoi(argv[1]);
	}
	
	
	char **c_ptr_array = (char **)malloc(line_num*sizeof(char*));
	int count = 0;
	while (1) {
		int i = 0;
		char * line = readaline(80);
		if (line == NULL) {break;}
		else {
			while (i < line_num) {
				c_ptr_array[i] = c_ptr_array[i+1];		
				i++;
			}
			c_ptr_array[line_num-1] = line;
			count += 1;
		}
	}
	int print_times;
	if (count < line_num) {
		print_times = count;
	}
	else {
		print_times = line_num;
	}
	int j = 0;
	while (j < print_times){
		printf("%s\n", c_ptr_array[line_num - print_times + j]);
		j++;
	}
	int k=0;
	while(k<line_num){
		free(c_ptr_array[k]);
		k++;
	}
	free(c_ptr_array);
	return 0;
}


char * readaline(int max) {
	char *ptr = NULL;
	char *line_array = (char *)malloc(max*sizeof(char));
	char stringlen;
	ptr = fgets(line_array, max, stdin);
	stringlen = strlen(line_array);
	line_array[stringlen-1] = '\0';
	if (ptr == NULL) {
		return NULL;
	} else {
		return line_array;
	}
}
