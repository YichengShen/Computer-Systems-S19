#include <stdio.h>

int readline(int text[40], int length);
int * findmatch(int pattern[40], int text[40], int patlen, int txtlen);
int printmessage(int *position, int text[40], int patlen, int txtlen);



int main() {
   int text[40], pattern[40], *position;
   int textlen, patternlen;

   printf("Enter text: ");
   textlen = readline(text, 40);

   printf("Enter pattern: ");
   patternlen = readline(pattern, 40);

   position = findmatch(pattern, text, patternlen, textlen); 

   printmessage(position, text, patternlen, textlen);
   return 0;
}

int readline(int text[40], int length) {
	int lenTxt = 0;
	while (1){
		if (lenTxt > length-1) {
			//this while here eats up the extra chars after 40 chars
			while (1) {
				int a = getchar();
				if (a == '\n') break;
			}
			break;
		}	
		int ic = getchar();
		if (ic < 0) {break;}
		if (ic == '\n') break;
		*(text+lenTxt) = ic;
		lenTxt ++;
	}
	return lenTxt;
}


int * findmatch(int pattern[40], int text[40], int patlen, int txtlen) {
	int *start;
	int i;
	for (i = 0; i < txtlen; i++) {
		int j = 0;
		while (1) {
			if ( (i + j) >= txtlen || j > patlen) break;
			if ((*(text + i + j) == *(pattern + j) || *(pattern + j) == 63)) {
				j ++;
			}
			else {break;}
			if ( j == patlen) {
				start = (text + i);
				return start;
			}
		}
	}
	return start;
}


int printmessage(int *position, int text[40], int patlen, int txtlen) {
	int char_position = abs(text - position) + 1;
	if ( *position == 0 ) {
		printf("%s", "no match");
	}
	else {
		printf("The pattern was found at char %d. The remaining text chars are: ", char_position );
		int times = 0;
		while (1) {
			if (times > (txtlen - char_position - patlen) ) break;
			putchar(*(position + patlen + times));
			times ++;
		}
	}
	printf("\n");
	return 0;
}
