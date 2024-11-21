#include <stdio.h>

int jePrestupny(int rok)
{
    return (rok % 4 == 0 && rok % 100 != 0) || (rok % 400 == 0);
    /*
    if ((rok % 4 == 0 && rok % 100 != 0) || rok % 400 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    */
}

int JeLichy(int rok)
{
    return rok % 2 == 1;
}

int main()
{
    printf("Rok\tPrestupny\tLichy\n");
    printf("1000\t%d\t\t%d\n", jePrestupny(1000), JeLichy(1000));
    printf("2000\t%d\t\t%d\n", jePrestupny(2000), JeLichy(2000));
    printf("2002\t%d\t\t%d\n", jePrestupny(2002), JeLichy(2002));
    printf("2012\t%d\t\t%d\n", jePrestupny(2012), JeLichy(2012));
    printf("2022\t%d\t\t%d\n", jePrestupny(2022), JeLichy(2022));
    printf("2200\t%d\t\t%d\n", jePrestupny(2200), JeLichy(2200));
    printf("2201\t%d\t\t%d\n", jePrestupny(2021), JeLichy(2021));
    printf("2201\t%d\t\t%d\n", jePrestupny(2021), JeLichy(2021));


    return 0;
}
