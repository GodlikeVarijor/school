#include <stdio.h>

int main() 
{
    double i;

    printf("Napis cas v sekundach, za ktery zaznel hrom po udereni blesku: ");
    scanf("%lf", &i);

    double b = i * 340;

    if (b >= 1000)
    {
        printf("Blesk uderil ve vzdalenosti %lf kilometru \n", b / 1000);
    }
    else
    {
        printf("Blesk uderil ve vzdalenosti %lf metru \n", b);
    }
    
    return 0;
}
