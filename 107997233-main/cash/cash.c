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
    return cents; //returns the value of cents to the int cents, could also return a number e.g 0 but that is not helpful in this example
}

int calculate_quarters(int cents)
{
    int quarters = 0;  // create an int called quarters and set it to 0 to store quarter value
    while (cents >= 25) // while loop checks that cents is greater than or equal to 25, if yes then execute
    {
        cents = cents - 25; //recall cents and then make cents equal to cents - 25
        quarters++; //add one to the int quarters and repeat until the while loop is no longer valid
    }
    return quarters; //return the value of quarters to int quarters and move to the next line of code as the while loop is no longer valid
}

int calculate_dimes(int cents)
{
    int dimes = 0; // create an int called dimes and set it to 0 to store dimes value
    while (cents >= 10) // while loop checks that cents is greater than or equal to 10, if yes then execute
    {
        cents = cents - 10; //recall cents and then make cents equal to cents - 10
        dimes++; //add one to the int dimes and repeat until the while loop is no longer valid
    }
    return dimes; //return the value of dimes to int dimes and move to the next line of code as the while loop is no longer valid
}

int calculate_nickels(int cents)
{
    int nickels = 0; // create an int called nickels and set it to 0 to store nickels value
    while (cents >= 5) // while loop checks that cents is greater than or equal to 5, if yes then execute
    {
        cents = cents - 5; //recall cents and then make cents equal to cents - 5
        nickels++; //add one to the int nickels and repeat until the while loop is no longer valid
    }
    return nickels; //return the value of nickels to int nickels and move to the next line of code as the while loop is no longer valid
}

int calculate_pennies(int cents)
{
    int pennies = 0; // create an int called pennies and set it to 0 to store pennies value
    while (cents >= 1) // while loop checks that cents is greater than or equal to 1, if yes then execute
    {
        cents = cents - 1; //recall cents and then make cents equal to cents - 1
        pennies++; //add one to the int pennies and repeat until the while loop is no longer valid
    }
    return pennies; //return the value of pennies to int pennies and move to the next line of code as the while loop is no longer valid
}
