#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
    printf("%i quarters\n", quarters); //print number of quarters required
    printf("%i dimes\n", dimes); //print number of dimes required
    printf("%i nickels\n", nickels); //print number of nickels required
    printf("%i pennies\n", pennies); //print number of pennies required
}

int get_cents(void)
{
    int cents; // create an int called cents to store the user input
    do
    {
        cents = get_int("Change owed: "); // print Change owed to promt input and store input to cents using get_int. get_int only allows numbers
    }
    while (cents < 0); //loop until a value greater than 0 is entered
    return cents;
}

int calculate_quarters(int cents)
{
    int quarters;  // create an int called quarters and set it to 0 to store quarter value
    if (cents >= 25 && cents <= 49)
    {
        return quarters = 1;
    }
    else if (cents >= 50 && cents <= 74)
    {
        return quarters = 2;
    }
    else if (cents >= 75 && cents <= 99)
    {
        return quarters = 3;
    }
    else if (cents >= 100 && cents <= 124)
    {
        return quarters = 4;
    }
    else if (cents >= 125 && cents <= 149)
    {
        return quarters = 5;
    }
    else if (cents >= 150 && cents <= 174)
    {
        return quarters = 6;
    }
    else if (cents >= 75 && cents <= 99)
    {
        return quarters = 7;
    }
    else if (cents >= 75 && cents <= 99)
    {
        return quarters = 8;
    }
    return 0;
}


int calculate_dimes(int cents)
{
    int dimes;  // create an int called dimes to store dime value
    if (cents >= 10 && cents <= 19)
    {
        return dimes = 1;
    }
    else if (cents >= 20 && cents <= 29)
    {
        return dimes = 2;
    }
    else if (cents >= 30 && cents <= 39)
    {
        return dimes = 3;
    }
    else if (cents >= 40 && cents <= 49)
    {
        return dimes = 4;
    }
    else if (cents >= 50 && cents <= 59)
    {
        return dimes = 5;
    }
    else if (cents >= 60 && cents <= 69)
    {
        return dimes = 6;
    }
    else if (cents >= 70 && cents <= 79)
    {
        return dimes = 7;
    }
    else if (cents >= 80 && cents <= 89)
    {
        return dimes = 8;
    }
    else if (cents >= 90 && cents <= 99)
    {
        return dimes = 9;
    }
    return 0;
}

int calculate_nickels(int cents)
{
    int nickels;  // create an int called nickels to store nickel value
    if (cents >= 5 && cents <= 9)
    {
        return nickels = 1;
    }
    else if (cents >= 10 && cents <= 14)
    {
        return nickels = 2;
    }
    else if (cents >= 15 && cents <= 19)
    {
        return nickels = 3;
    }
    else if (cents >= 20 && cents <= 24)
    {
        return nickels = 4;
    }
    else if (cents >= 25 && cents <= 29)
    {
        return nickels = 5;
    }
    else if (cents >= 30 && cents <= 34)
    {
        return nickels = 6;
    }
    else if (cents >= 35 && cents <= 39)
    {
        return nickels = 7;
    }
    else if (cents >= 40 && cents <= 44)
    {
        return nickels = 8;
    }
    else if (cents >= 45 && cents <= 49)
    {
        return nickels = 9;
    }
    else if (cents >= 50 && cents <= 54)
    {
        return nickels = 10;
    }
    return 0;
}

int calculate_pennies(int cents)
{
    int pennies; // create an int called pennies to store penny value
    if (cents >= 1 && cents < 2)
    {
        return pennies = 1;
    }
    else if (cents >= 2 && cents < 3)
    {
        return pennies = 2;
    }
    else if (cents >= 3 && cents < 4)
    {
        return pennies = 3;
    }
    else if (cents >= 4 && cents < 5)
    {
        return pennies = 4;
    }
    return 0;
}