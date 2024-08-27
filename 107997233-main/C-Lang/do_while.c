//EXAMPLE OF DO WHILE LOOP
#include <cs50.h>
#include <stdio.h>

int main(void)
{
int m = 0;
	do
  	{
        		printf("Enter a positive integer no greater than 23: \n");
        		int n = get_int();
		        //printf(“You entered %i \n");
   	 }
   	 while (int n < 0 || int n > 23);
}
 
