#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    
    // Declare variables
    float amount;
    int coins = 0;
    
    // Prompt user for change owed
    do  
    {
        amount = get_float("Change Owed: $");
    }
    while (amount <= 0);
    
    // Convert ammount owned into cents
    int cents = round(amount * 100);
    
    // Use greedy algorithm
    while (cents >= 25)
    {
       cents = cents - 25;
       coins++;
    }
    while (cents >= 10)
    {
       cents = cents - 10;
       coins++;
    }
    while (cents >= 5)
    {
       cents = cents - 5;
       coins++;
    }
    while (cents >= 1)
    {
       cents = cents - 1;
       coins++;
    }
    printf("%i\n", coins);
    
}
