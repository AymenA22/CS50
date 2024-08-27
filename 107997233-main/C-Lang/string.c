#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int name;
    do
    {
        string name = get_string("Enter your Name: ");
    }
    while (name < 1);

    int element[length];
    // Set element 0 of the array to 1
    element[0] = 1;
    // Print the first element of the array
    printf("%i\n", element[0]);

    for (int i = 1; i < length; i++ )
    {
        // Make the current element twice its previous
        element[i] = 2 * element[i - 1];

        // Print te current element
        printf("%i\n", element[i]);
    }
}