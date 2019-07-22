/*
Name: vigenere.c
Written by: John C. Johnson
Useage: ./vigenere [alpha-key]
Expected results: If user enters ./vigenere followed by 1 alphabetical key,
the program should get plain text from the user to be enciphered and proceed
to encipher the text via vigenere cipher, thus outputting the ciphertext.
If the user fails to input a single key or if that key contains
non-alphabetical chars, then the program should return an error message and
exit with an exit code of 1.
Example: 
./vigenere bacon
plaintext: And this is CS50!
ciphertext: Bnf hujs kg PT50!
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_SIZE 128
typedef char * string;

// gets a line of text to newline
string getLine();

// Gives error message to user.
void error(void);

// Performs math for cipher
int caesar(char letter, int number, int casetype);

int main(int argc, string argv[]) {
	// Checks that exactly 1 command line argument is entered. 
	if (argc != 2) {
		error();
		return 1;
	}

	string key = argv[1];
	// Length of key used repeatedly in code.
	int n = strlen(key);

	// Make sure each char in key isalpha,
	for (int check = 0; check < n; check++) {
		if (!isalpha(key[check])) {
			error();
		}
	}

	printf("plaintext: ");
	string plain = getLine();

	printf("ciphertext: ");

	int upper = 'A';
	int lower = 'a';
	int k = 0, cipher = 0;
	// Itterate through plaintext char and key char
	for (int i = 0, j = 0, m = strlen(plain); i < m; i++) {
		// Make lower and upper letter key same size and 0 index alphabet
		k = toupper(key[j]) - upper;
		// Maintain Case
		if (isupper(plain[i])) {
			// Only change keys index if alphabeticial char is givin
			j = (j + 1) % n;
			// % upper gets letter indexed at 0. i.e. A = 0. % 26 wraps arround
			cipher = caesar(plain[i], k, upper);
			printf("%c", cipher);
		}
		else if (islower(plain[i])) {
			j = (j + 1) % n;
			// % lower gets letter indexed at 0. i.e. a = 0. % 26 wraps arround
			cipher = caesar(plain[i], k, lower);
			printf("%c", cipher);
		}
		else
			printf("%c", plain[i]);
	}

	printf("\n");
	return 0;
}

string getLine() {
	// growable string for chars
	string str = NULL;
	// size of str
	size_t tmpSize = 0;
	// number of chars actually in str
	size_t size = 0;
	// Stores char of next char to insert into string
	int c = CHAR_MAX;

	// Get Chars until newline or EOF is reached
	while ((c = fgetc(stdin)) != '\n' && c != EOF) {
		// grow str if actual size is bigger than temp size
		if (size + 1 > tmpSize) {
			if (tmpSize == 0)
				tmpSize = MAX_SIZE;
			else if (tmpSize <= (UINT_MAX / 2))
				tmpSize *= 2;
			else {
				free(str);
				return NULL;
			}
			// Resize temp
			string temp = realloc(str, tmpSize * sizeof(char));
			if (!temp) {
				free(str);
				return NULL;
			}
			str = temp;
		}
		str[size++] = c;
	}
	// String empty or too big
	if (size == 0 && c == EOF)
		return NULL;

	string min = malloc((size + 1) * sizeof(char));
	strncpy(min, str, size);
	free(str);
	min[size] = '\0';

	return min;
}

// Prints instructions to user if program used not as intended.
void error(void) {
	printf("Please give one and only one alpha-type key.\n");
	printf("Useage: ./vigenere [alpha-key]\n");
	printf("Example: ./vigenere bacon\n");
	exit('B');
}

// char in plaintext letter, number = key, casetype = case i.e. upper/lower 
int caesar(char letter, int number, int casetype) {
	// Moves char x spaces in key
	int enciphered = (((letter + number) % casetype) % 26) + casetype;
	return enciphered;
}
