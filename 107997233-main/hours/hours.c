#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks]; //array called hours for number of weeks

    for (int i = 0; i < weeks; i++) //for each iteration it will ask the user for how many hours
    {
        hours[i] = get_int("Week %i HW Hours: ", i); //this creates the array from above by
        // asking the user and inputting each answer into the next array element
        //i[0] = user input for week 1 e.g 5 hours
        //i[1] = user input for week 2 e.g 10 hours
    }

    char output; //asking user if they want Total or Average
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
        //output just ensures UPPER CASE and prompts the user
    }
    while (output != 'T' && output != 'A');
    //the DO WHILE LOOP will keep looping until the user give input

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
    //prints the calculation as below
}

// TODO: complete the calc_hours function
// Sum all the hours collected
// Return value for if the user asked for Total or Average

float calc_hours(int hours[], int weeks, char output)
{
    int total = 0;
    for (int i = 0; i < weeks; i++)
    {
        total += hours[i];
    }
    //this will keep adding each element of the array hours
    // until i is equal to the number of weeks then it will
    // stop and break out of the loop
    //e.g 5h wk1 (element 0), 2hrs wk2 (element 1)
    // total = i = 0 which is less than 2 (weeks) so add 5h
    // total is now 5 and increment i by 1 because i is now 1
    // total (5) + 2 for week 2 and increment i by 1
    // i is now 2 and therefore the loop ends
    // end of total hours loop

    // check for users input T or A
    // IF output is equal == to T then return inside the brackets
    // and return total, otherwise do not enter the brackets
    // and jump to the next line
    if (output == 'T') // single quotation marks for comparitor
    {
        return (float) total; //changing variable to float
        //in case the number is a decimal
    }
    return (float) total / weeks; //changing variable to float
    //in case the number is a decimal
}