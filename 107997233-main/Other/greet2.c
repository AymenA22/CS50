#include <cs50.h>
#include <stdio.h>
//command line arguements

int main(int argc, string argv[])
//argc is the counter for how many inputs are in the
//array argv
//this allows you to enter text in the command line directly
{
    if (argc == 2)
    {
        printf("hello, %s\n", argv[1]);
    }
    else
    {
        printf("hello, world\n");
    }
}
// now type ./greet Aymen
//if i do not enter anything it will print hello world