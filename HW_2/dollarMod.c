//Yicheng Shen
//HW_2
//Part C
//1/30/2019

#include <stdlib.h>
#include <stdio.h>


void pay_amount(int dollars, int *twenties, int *tens, int *fives, int *ones);


int amt;
int b_20, b_10, b_5, b_1;


int main() {
	printf("Enter a dollar amount: ");
	scanf("%d", &amt);

	pay_amount(amt, &b_20, &b_10, &b_5, &b_1);

	return 0;
}


void pay_amount(int dollars, int *twenties, int *tens, int *fives, int *ones) {
	
	*twenties = amt / 20;
	amt -= 20 * *twenties;
	*tens = amt / 10;
	amt -= 10 * *tens;
	*fives = amt / 5;
	amt -= 5 * *fives;
	*ones = amt / 1;

	printf("$20 bills: %d \n", *twenties);
	printf("$10 bills: %d \n", *tens);
	printf(" $5 bills: %d \n", *fives);
	printf(" $1 bills: %d \n", *ones);

}

