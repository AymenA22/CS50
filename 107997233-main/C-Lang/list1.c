#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main (int argc, char *argv[])
{
    node *list = NULL;

    // command line ./list 1 2 3
    // so we need to se int argc, string argv)

    for (int i = 1; i < argc; i++) // start at 1 because the first value is ./list
    {
        int number = atoi(argv[i]); // atoi convers ascii to interger

        node * n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }
        n->number = number; // from line 21
        n->next = NULL; // clears garbage value

        n->next = list; // prepend - node must have a next field that points to the current beginning of the list
        list = n;
    }

    node *ptr = list; // set to the first node of the list

    // for (node *ptr = list; ptr != NULL; ptr = ptr->next)
    //or the below while line

    while (ptr != NULL)
    {
        printf("%i\n", ptr->number);
        ptr = ptr->next; // this will make the pointer now look to the next node
        // because it is looking at the next field

        // eventually it will equal NULL and the while loop will stop
    }

    // free memory using a temp variable next to hold the ->next value
    ptr = list;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
}