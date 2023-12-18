/*
Name: encrypt.c
Written by: John C. Johnson
Usage: ./encrypt [word]
Example:
./hash CSft
"50C8rfvcYwAPI"

The program is designed to encrypt a string with DES for CS50/CS50x's crack.c
to use to test hashes to check if your program works.
*/

#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./hash [word]\n");
        return 1;
    }
    
    char *salt = "50";
    char *word = argv[1];
    char *hash = crypt(word, salt);
    printf("%s\n", hash);
    return 0;
}
