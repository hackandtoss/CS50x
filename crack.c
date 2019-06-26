/*
Name: crack.c
Written by: John C. Johnson
Usage: ./crack [hash]
Expected results: Proper execution of program, when supplied a hash gererated
by an alpha key, should retun, printed to the screen, to the user the hash
cracked .If the user fails to enter one and only one hash, the program should
print to the screen with instructions and exit with exit code of 1.
Example:
./crack 50b9E0A2arFdI
Han
./crack
Usage: ./crack [hash]
*/

#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Make sure user gave one and only one hash
    if (argc != 2)
    {
        printf("Usage: ./crack [hash]\n");
        return 1;
    }
    
    // (String is an array of chars) copy then expanded the array of chars
    char *salt = "50";
    char first[2];
    char second[3];
    char third[4];
    char fourth[5];
    char *hash = argv[1];
    // Itterate over ascii letters from 'A' to 'z'
    for (int i = 'A'; i <= 'z'; i++)
    {
        first[0] = i;
        first[1] = '\0';
        // Check if hash matches current string hashed
        if (strcmp(hash, crypt(first, salt)) == 0)
        {
            printf("%s\n", first);
            // Wanted the program to termiate once hash matched
            return 0;
        }
        // Nested for loops got me the next char to be added.
        for (int j = 'A'; j <= 'z'; j++)
        {
            // Copy array of chars from each previous array of chars
            second[0] = first[0];
            second[1] = j;
            second[2] = '\0';
            if (strcmp(hash, crypt(second, salt)) == 0)
            {
                printf("%s\n", second);
                return 0;
            }
            for (int k = 'A'; k <= 'z'; k++)
            {
                third[0] = second[0];
                third[1] = second[1];
                third[2] = k;
                third[3] = '\0';
                if (strcmp(hash, crypt(third, salt)) == 0)
                { 
                    printf("%s\n", third);
                    return 0;
                }
                for (int m = 'A'; m <= 'z'; m++)
                {
                    fourth[0] = third[0];
                    fourth[1] = third[1];
                    fourth[2] = third[2];
                    fourth[3] = m;
                    fourth[4] = '\0';
                    if (strcmp(hash, crypt(fourth, salt)) == 0)
                    { 
                        printf("%s\n", fourth);
                        return 0;
                    }
                }
            }
        }
    }
    return 0;
}