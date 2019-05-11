//Yicheng Shen
//HW_1 
//1/24/2019


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int main() {
  int lineCount = 0;
  int numLines = 0;
  int numChars = 0;
  int numWords = 0;
  int numWordsChar = 0;
  int preIsSpace = 1; // assume the before the first word, there is a space. So that the first word is taken into account

  printf("Enter text.  Use an empty line to stop.\n");
  
  while (1) {
      int ic = getchar();
      if (ic < 0)    //EOF encountered
          break;
      char c = (char) ic;
      if (c == '\n' && lineCount == 0){ //Empty line
          if (preIsSpace == 0) {
	  	numWords ++;
	  }
          break; 
      }

      numChars ++;
      //Count words
      if (!isspace(c) && preIsSpace == 1) { //if current char is not space & previous char is a space
	  numWords ++;
      }

      if (isspace(c)){
	  preIsSpace = 1;
      }
      else{
	  preIsSpace = 0;
	  numWordsChar ++;
      }
      //-----
      if (c == '\n') {
          numLines ++;
          lineCount = 0;
      }
      else
          lineCount ++;
  }
  printf("Your text has %d lines and %d characters.\n", numLines, numChars);
  double average = (double) numWordsChar / numWords;
  printf("Your text has %d words, with an average length of %.2f. \n", numWords, average);
}
