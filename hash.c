/*
Name: hash.c
Written by: John C. Johnson
Usage: ./hash [word]
Example:
./hash CSft
"50C8rfvcYwAPI"

Program is designed to gereate valid DES baised hashes for CS50/CS50x's crack.c
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
    // Used quotes becuse it was easier to copy for hard coded strings.
    printf("\"%s\"\n", hash);
    return 0;
}