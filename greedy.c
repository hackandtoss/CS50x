/*
Greedy.c
Usage: ./greedy - Greedy request a float from the user in the for of change owed
Result: Greedy returns an int, the number of coins to give back to the user
*/
#ifdef CS50X
#include <cs50.h>
#endif
#include <stdio.h>
#include <math.h>

//Request amount of change from the user.
float GetChange(void);

//Calcluates how many coins to give back to the user baised off the Users input
int GiveCoins(float n);

int main(void)
{
    float owed = GetChange();
    int coins;
    //Checks if any change is owed at all and if not return 0 coins owed
    if (owed == 0.0)
    {
        coins = 0;
    }
    else
    {
        coins = GiveCoins(owed);
    }
    //Prints out coins owed
    printf("%i\n", coins);
    return 0;
}

//Uses do while loop to get a non-negitive float from the user and reprompts if the user doesnt comply
float GetChange(void)
{
    float n = 0; 
    do
    {
        printf("How much change is oweded?\n");
#ifdef CS50X
        n = get_float();
#else
		scanf("%f", &n);
#endif
    }
    while (n < 0.0);
    return n;
}

//Uses a while loop starting from the largest denominanation to the samallest
int GiveCoins(float n)
{
    //n is mutiplied by 100 to better work with the numbers
    float rounded = round(n * 100.0);
    int change = (int) rounded;
    //Each denonamation is assigned to 0 to be added to the total sum if no coins in the denonamtion are needed.
    int quarters = 0;
    int dimes = 0;
    int nickles = 0;
    int pennies = 0;
    
    while (change > 0)
    {
        /*
        Each Denonamation takes the current change and divides it by that denonamation to get the # of coins for that denonamation
        Remaining change if calculated by current change % denonamation.
        */
        if (change >= 25)
        {
            quarters = change / 25;
            change = change % 25;
        }
        else if (change < 25 && change >= 10)
        {
            dimes = change / 10;
            change = change % 10;
        }
        else if (change < 10 && change >= 5)
        {
            nickles = change / 5;
            change = change % 5;
        }
        else
        {
            pennies = change;
            change = change % 1;
        }
    }
    //Total number of coins is summed up by adding each total number per denonamation
    int total = quarters + dimes + nickles + pennies;
    return total;
}
