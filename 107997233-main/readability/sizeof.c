#include <stdio.h>
#include <cs50.h>

int main()
{
    string text = get_string("Text: ");
    int i = 0;
    printf("%lu\n", sizeof(char));
    printf("%lu\n", sizeof(int));
    printf("%lu\n", sizeof(float));
    printf("%lu\n", sizeof(char));

    return 0;
}