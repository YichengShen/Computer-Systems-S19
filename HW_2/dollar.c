//Yicheng Shen
//HW_2
//Part B
//1/30/2019

#include <stdlib.h>
#include <stdio.h>


int amt;
int b_20, b_10, b_5, b_1;


int main(){
	printf("Enter a dollar amount: ");
	scanf("%d", &amt);
	
	b_20 = amt / 20;
	amt -= 20 * b_20;
	b_10 = amt / 10;
	amt -= 10 * b_10;
	b_5 = amt / 5;
	amt -= 5 * b_5;
	b_1 = amt / 1;

	printf("$20 bills: %d \n", b_20);
	printf("$10 bills: %d \n", b_10);
	printf(" $5 bills: %d \n", b_5);
	printf(" $1 bills: %d \n", b_1);

	return 0;
}
