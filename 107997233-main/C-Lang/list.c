#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

int main (void)
{
    int list[3];

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    for (int i = 0; i< 3; i++)
    {
        printf("%i\n", list[i]);
    }
}


// use malloc to allocate memory
int main (void)
{
    int *list = malloc(3 * sizeof(int)); // as a pointer

    // check for NULL value
    if (list == NULL)
    {
        return 1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    for (int i = 0; i< 3; i++)
    {
        printf("%i\n", list[i]); // if just i then it would print 0, 1, 2
    }
}


// how to add for more memory spaces (bytes)
int main (void)
{
    int *list = malloc(3 * x=sizeof(int)); // as a pointer

    // check for NULL value
    if (list == NULL)
    {
        return 1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    // create a new memory size of 4 and check for NULL
    // free memory if NULL then exit 1
    int *tmp = malloc(4 * sizeof(int))
    if (tmp == NULL)
    {
        free(list);
        return 1;
    }

    for (int i = 0; i < 3; i++)
    {
        tmp[i] = list[i];
    }
    tmp[3] = 4;

    free (list);

    // now POINT list at tmp to use 4 bytes instead of 3 bytes

    list = tmp

    for (int i = 0; i < 3; i++)
    {
        printf("%i\n", list[i]); // if just i then it would print 0, 1, 2
    }

    free (list);
    return 0;
}






// A SIMPLIFIED METHOD THAT USES LESS CODE

int main (void)
{
    int *list = malloc(3 * x=sizeof(int)); // as a pointer

    // check for NULL value
    if (list == NULL)
    {
        return 1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    // USE INT *TMP PURELY TO ALLOW THE NULL CHECK
    // OTHERWISE WE COULD JUST USE LIST = REALLOC
    int *tmp = realloc(list, 4 * sizeof(int));
    if (tmp == NULL)
    {
        free(list);
        return 1;
    }

    list = tmp // MAKE LIST EQUAL TO TMP BECAUSE THE MEMORY IS NOT NULL

    list[3] = 4; // MAKE ELEMENT 3 EQUAL TO 4 OR ANY OTHER CHOSEN VALUE

    free (list);

    for (int i = 0; i < 3; i++)
    {
        printf("%i\n", list[i]); // if just i then it would print 0, 1, 2
    }

    free (list);
    return 0;
}