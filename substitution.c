#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// Submission for week 2 "Substitution Cipher using Key"
// By Duncan Starkenburg aka EvilDunk

int main(int argc, string argv[]) // Get Key from Command Line
{
    string key = argv[1];
    // Validate Key
    // Check for blank command line
    if (argc == 1)
    {
        printf("Usage: ./substitution <key>\n");
        return 1;
    }
    // Check for invalid length
    if (strlen(key) != 26)
    {
        printf("--INVALID KEY--\n");
        printf("Key should contain 26 unique letters.\n");
        return 1;
    }

    //|| LENGTH IS VALID

    // Check for numbers
    char digits[] = "0123456789";
    char *ptr = strpbrk(key, digits);
    if (ptr != NULL)
    {
        printf("--INVALID KEY--\n");
        printf("Key cannot contain numbers\n");
        return 1;
    }
    // Check for duplicates
    int count;
    for (int i = 0; i < strlen(key); i++)
    {
        count = 1;
        for (int j = i + 1; j < strlen(key); j++)
        {
            if (key[i] == key[j] && key[i] != ' ')
            {
                count++;
                // Set argc[1][j] to 0 to avoid double crossing characters
                key[j] = '0';
            }
        }
        // A character is considered as duplicate if count is greater than 1
        if (count > 1 && key[i] != '0')
        {
            printf("--INVALID KEY--\n");
            printf("Key cannot contain duplicates.\n");
            return 1;
        }
    }

    //|| KEY IS VALID

    printf("Key is valid!\n");

    // Get plaintext
    string text = get_string("plaintext: ");
    string alphaL = "abcdefghijklmnopqrstuvwxyz";
    string alphaU = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // Enciper plaintexts
    printf("ciphertext: ");
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        int len1 = strlen(alphaL);
        int position;
        int len2 = strlen(alphaU);
        int position2;
        // Test for cases
        if (islower(text[i]))
        {
            for (int j = 0; j < len1; j++)
            {
                if (alphaL[j] == text[i])
                {
                    position = j;
                }
            }
            printf("%c", tolower(key[position]));
        }
        else if (isupper(text[i]))
        {
            for (int j = 0; j < len2; j++)
            {
                if (alphaU[j] == text[i])
                {
                    position2 = j;
                }
            }
            printf("%c", toupper(key[position2]));
        }

        // Test for special characters
        else if (text[i] == ' ' || text[i] == '.' || text[i] == ',' || text[i] == '!' || text[i] == '?' || isdigit(text[i]))
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
    return 0;


}