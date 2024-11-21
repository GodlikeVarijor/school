#include <stdio.h>

int main()
{

    int x1, y1, x2, y2;
    printf("Zadejte prvni vektor (prvne x1, pak mezera, pak y1): ");
    scanf("%d %d", &x1, &y1);
    printf("Zadejte druhy vektor (prvne x2, pak mezera, pak y2): ");
    scanf("%d %d", &x2, &y2);

    printf("Soucet vektoru: %d %d\n", x1 + x2, y1 + y2);


    return 0;
}