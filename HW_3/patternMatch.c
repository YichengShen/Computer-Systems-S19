#include <stdio.h>


int main() {   int text[40], pattern[40], *position;   int textlen, patternlen;   printf("Enter text: ");   textlen = readline(text, 40);   printf("Enter pattern: ");   patternlen = readline(pattern, 40);   position = findmatch(pattern, text, patternlen, textlen);   printmessage(position, text, patternlen, textlen);}

