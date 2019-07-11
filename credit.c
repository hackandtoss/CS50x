/*
This project is desgined as means for myself to challenge my skillset in c programming as a lesson for CS50x on Edx
Program name: Credit.c
Written by: John C. Johnson
Usage: ./credit
Expected outcome: User inputs Credit Card Number after being prompted Number: non-numeric numbers return a Retry: prompt.
all goes well program should output Visa, Amex, Mastercard or Invalid. No other types of cards are excepted. 
Program should return 0.
i.e. Number: 5555555555554444
MASTERCARD
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef char * string;

//Checksum returns ture or false
bool get_checksum(long long n);

//Gets the Card's ID
int get_id(long long z);

int main(void) {
	//Request Credit Card # from user
	printf("Number: ");
	long long int number = 0;
	scanf("%lli", &number);
	//Checks that credit card is correct length without doing math
	if (number < 4000000000000 || number > 5600000000000000) {
		printf("INVALID\n");
	}
	else {
		//takes CC Number and performs checksum
		if (!get_checksum(number))
			printf("INVALID\n");
		//Finds the identifying numbers of the credit card.
		int id = get_id(number);
		//program must end with printf VISA\n AMEX\n MASTERCARD\n or INVALID\n
		if (id >= 51 && id <= 55) 
			printf("MASTERCARD\n");
		else if (id == 37 || id == 34) 
			printf("AMEX\n");
		else if (id >= 40 && id <= 49)
			printf("VISA\n");
		else 
			printf("INVALID\n");
	}
	return 0;
}

//Calculates CC Checksum returns bool
bool get_checksum(long long n) {
	int count = 0;
	long long c = n;
	//finds length of credit card
	while (c != 0) {
		c = c / 10;
		count++;
	}
	//finds stopping point of first and second loop for doing rolling sum of checksum number
	int first = 0;
	int last = 0;
	if (count % 2 == 0) {
		first = count / 2;
		last = first;
	}
	else {
		first = count / 2;
		last = first + 1;
	}
	int sum = 0;
	long long a = n;
	for (int i = 0; i < first; i++) {
		long long x = a % 10;
		a = (a - x) / 10;
		x = a % 10;
		a = (a - x) / 10;
		long long digits = x * 2;
		if (digits >= 10) {
			sum = sum + (1 + (digits % 10));
		}
		else {
			sum = sum + (digits);
		}
	}
	long long b = n;
	for (int i = 0; i < last; i++) {
		long long y = b % 10;
		sum = sum + y;
		b = (b - y) / 100;
	}
	bool tf = 0;
	//checks if number ends in 0 and returns true if 0 and false if != 0
	if (sum % 10 == 0) {
		tf = true;
	}
	else {
		tf = false;
	}
	return tf;
}

//Takes CC # finds the Identifing numbers of thw credit card and returns that number
int get_id(long long z) {
	int id;
	//keep itterating over number until only first 2 numbers remain
	while (z != 0) {
		z = z / 10;
		if (z < 100) {
			id = z % 100;
			break;
		}
	}
	return id;
}


