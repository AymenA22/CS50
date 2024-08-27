#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What's your name?\n"); //get string is used to record user input
    printf("hello, %s\n", name); //print hello, "get_string" which should be name. %s is the placeholder for the string and \n is a new line
}