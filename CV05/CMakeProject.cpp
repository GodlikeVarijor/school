//TODO: Doplňte kód o funkci vektorovySoucin vypocita vektorovy soucin dvou vektoru. šiměte si, že vektorový součin je definován jen prostoru, a že výsledkem vektorového součinu dvou vektorů je vektor. Pro souřadnice vektorového součinu w vektorů u = (u1; u2; u3) a v = (v1; v2; v3) platí: w = u × v = (u2v3 - u3v2; u3v1 - u1v3; u1v2 - u2v1).

#include <cmath>
#include <stdio.h>

void soucet(double a[3], double b[3], double c[3])
{
    for (int i = 0; i < 3; i++)
    {
        c[i] = a[i] + b[i];     //vezme a1,b1 a secte je do c1
    }
}

double velikost(double a[3])
{
    double v = 0;
    for (int i = 0; i < 3; i++)
    {
        v += a[i] * a[i];   //vezme a1,a2,a3 a secte je do v
    }
    return sqrt(v); //vrati odmocninu z v
}

double skalarniSoucin(double a[3], double b[3])
{
    double s = 0;
    for (int i = 0; i < 3; i++)
    {
        s += a[i] * b[i];   //a1*b1 + a2*b2 + a3*b3
    }
    return s;
}

void vektorovySoucin(double a[3], double b[3], double c[3])
{
    c[0] = (a[1] * b[2]) - (a[2] * b[1]);  //a2*b3 - a3*b2
    c[1] = (a[2] * b[0]) - (a[0] * b[2]);  //a3*b1 - a1*b3
    c[2] = (a[0] * b[1]) - (a[1] * b[0]);  //a1*b2 - a2*b1
}

int main()
{
    double a[3], b[3], c[3];
    printf("Vektor A (3 hodnoty oddelene carkou): ");
    scanf("%lf,%lf,%lf", &a[0], &a[1], &a[2]);
    
    printf("Vektor B (3 hodnoty oddelene carkou): ");
    scanf("%lf,%lf,%lf", &b[0], &b[1], &b[2]);
    
    soucet(a, b, c);
    printf("Soucet A+B: (%.6f, %.6f, %.6f)\n", c[0], c[1], c[2]);
    printf("Velikost A: %.6f\n", velikost(a));
    printf("Velikost B: %.6f\n", velikost(b));
    printf("Skalarni soucin AB: %.6f\n", skalarniSoucin(a, b));
    
    vektorovySoucin(a, b, c);
    printf("Vektorovy soucin AB: (%.6f, %.6f, %.6f)\n", c[0], c[1], c[2]);
    return 0;
}