#include <cs50.h>
#include <stdio.h>

int main(void)
{
//Prompt user to input a positive interger between 1 and 8
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
//Setup grid for output
    for (int line = 0; line < height; line++) //calculate new lines
    {
        for (int space = height - line - 1; space > 0; space--) //calculate number of spaces
        {
            printf(" "); //print spaces
        }
        for (int tag = 0; tag < line; tag++) //calculate number of hashtags
        {
            printf("#"); //print hashtags
        }
        printf("#\n"); //print new line
    }
}