#include "FunExt.h"
#include <cfloat>
#include <climits>

using namespace std;

int main()
{
    double minY = -DBL_MAX; //bo to je nejmensi hodnota, kdyby tam nebylo -, tak by minY bylo rovno DBL_MAX, coz je extremne velka hodnota, takze by se podminka forloopu nevykonala
    int minX = INT_MAX;
    for (int x = 10; x <= 20; ++x)
    {
        double y = 5 - 3 * x + 2 * (x - 5) * (x - 5) - (x - 10) * (x - 10) * (x - 10);

        if (y > minY)
        {
            minY = y;
            minX = x;
        }
    }
    printf("Maximum value: %lf at x=%d\n", minY, minX);
    return 0;
}
