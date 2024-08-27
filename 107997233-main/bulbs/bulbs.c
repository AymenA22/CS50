#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;
void print_bulb(int bit);
int main(void)
{
    // Ask user to input a message and store to string called message
    string message = get_string("Message: ");
    /* this string "message" is just an array of char e.g char[]*/

    // Execute a "for loop" to cycle through each char in the message
    for (int i = 0, n = strlen(message); i < n;
         i++) /* int i set to 0 and n = string length of message; while i < n; keep incrementing i */
    {
        /* convert each char in the message to binary */
        char a = message[i];
        for (int j = BITS_IN_BYTE - 1; j >= 0; j--)
        /* set interger called j equal to BITS_IN_BYTE - 1 which is 8 - 1, then keep iterating this for loop while j is greater than
        or equal to 0. Every time the loop is complete, minus 1 from j until j is less than 0 then break out of this loop */
        {
            int bit = (a >> j) & 1; /* if j is greater than 0 then right shift the interger BIT will be equal to */

            print_bulb(bit); // recall the returned value from void print_bulb
        }
        printf("\n"); // print a new line
    }
}
// This will read the INT BIT and will then return the printf output back to MAIN VOID
void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}