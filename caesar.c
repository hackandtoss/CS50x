/*
Tmux Omqemd!
Name: caesar.c
Written by: John C Johnson
Usage: ./caesar [key]
Expected result: 1 commandline argugument after the program is requred.
that argument must be an int, the key, the number of chars to roate
each char. Successful implimentation of the program should result in
an encyphered text, by means of the caesar cypher. If user fails to enter
and argument count of no less or no more than 2 then the program should 
remind the user how to use the program then exit with exit code of 1
Example:
./caesar 12
plaintext: Hail Caesar!
cyphertext: Tmux Omqemd!
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#define MAX_SIZE 128
typedef char * string;

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

int main(int argc, char *argv[]) {
	// Makes sure a key is entered exits with exit code 1 if not.
	if (argc != 2) {
		printf("Usage: ./caesar [key]\n");
		return 1;
	}

	// Gets text to be encyphered
	printf("plaintext: ");
	string keyword = getLine();

	// Prints result of encyphered text after :
	printf("ciphertext: ");
	// atoi convers string to int
	int key = atoi(argv[1]);
	int upper = 'A';
	int lower = 'a';
	int new = 0; 
	// isupper/islower maintains case.
	for (int i = 0, n = strlen(keyword); i < n; i++) {
		if (isupper(keyword[i])) {
			// % upper gets letter indexed at 0. i.e. A = 0. % 26 wraps arround
			new = (((keyword[i] + key) % upper) % 26) + upper;
			printf("%c", new);
		}
		else if (islower(keyword[i])) {
			// % lower gets letter indexed at 0. i.e. a = 0. % 26 wraps arround
			new = (((keyword[i] + key) % lower) % 26) + lower;
			printf("%c", new);
		}
		else {
			printf("%c", keyword[i]);
		}
	}

	printf("\n");
	return 0;
}
