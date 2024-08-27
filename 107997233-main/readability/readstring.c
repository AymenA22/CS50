#include <stdio.h>
#include <string.h>
#include <cs50.h>

int main(void)
{
    string text = get_string("Text: ");
    // declaring string
    char str[50];

    // reading string
    scanf("%s",str);

    // print string
    printf("%s",str);

    return 0;
}