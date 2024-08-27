#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main()
{
/*  int a;
    int b;
    int c;
*/
    int a = get_int("What's A? ");
    int b = get_int("What's B? ");

/*  printf("Enter size A: \n");
    scanf("%lf", &A);

    printf("Enter size B: \n");
    scanf("%lf", &B);
*/
    double c = sqrt(a*a + b*b);

    printf("Side C: %.2f\n", c);
}