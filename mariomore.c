#include <cs50.h>
#include <stdio.h>

int main(void)
{   
    // Make variables
    int height;
    int row;
    int spaces;
    int hashes;
    
    // Get the number
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8); // Is the number 1-8?
    // If not 1-8, prompt user for height again
   
    // Count the rows
    for (row = 1; row <= height; row++)
    { 
        // Print spaces
        for (spaces = height - row; spaces > 0; spaces--)
        {
            printf(" ");
        }
        
        // Print hashes
        for (hashes = 0; hashes < row; hashes++)
        {
            printf("#");
        }
        
        // Print middle spaces
        printf("  ");
     
        // Print second hashes
        for (hashes = 0;hashes < row; hashes++)
        {
            printf("#");
        }
        
        // Start new line
        printf("\n");
        
    }
}
