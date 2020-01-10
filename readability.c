#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Submission for week 1 "Readability using Coleman-Liau Index"
// By Duncan Starkenburg aka EvilDunk



int main(void)
{
    // Prompt user for text input check for blanks
    string text;
    do
    {
        text = get_string("Text: ");
    }
    while (strlen(text) <= 0);
    int length = strlen(text);


    // Count letters
    float letters = 0;
    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }

    // Count words
    float words = 0;
    for (int i = 0; i < length; i++)
    {
        if (isblank(text[i]))
        {
            words++;
        }
    }
    words++;

    // Count sentences
    float sentences = 0;
    for (int i = 0; i < length; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
    }

    // Put everything together using Coleman-Liau Index
    float L = 0;
    float S = 0;

    if (words > 0)
    {
        L = (100 * letters) / words;
        S = (100 * sentences) / words;
    }

    float index = (0.0588 * L) - (0.296 * S) - 15.8;

    // Print results
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 1 && index < 16)
    {
        printf("Grade %.0f\n", index);
    }
    else
    {
        printf("Grade 16+\n");
    }

}