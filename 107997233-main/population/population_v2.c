#include <stdio.h>
#include <cs50.h>

int get_start(void); //get start size from void below
int get_end(void); //get end size from void below

int main(void)
{
    int start = get_start(); //Prompt for start size
    int end = get_end(); //Prompt for end size
//calculate result
    int years=0;
    while (start < end)
    {
        start = start + (start / 3) - (start / 4);
        years++;
    }
    printf("Years: %i\n", years);
}
//start size loop
int get_start(void)
{
    int start;
    do
    {
        start = get_int("Start Size: ");
    }
    while (start < end);
    return start;
}
//end size loop
int get_end(void)
{
    int end;
    do
    {
        end = get_int("End Size: ");
    }
    while (end < start);
    return end;
}