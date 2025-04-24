#include "xklimam00.h"
#include <iostream>
#include <algorithm>

int prunik(double zacatek1, double konec1, double zacatek2, double konec2,
           double* vysl_zacatek, double* vysl_konec) {
    if (zacatek1 > konec1) {
        std::swap(zacatek1, konec1);
    }
    if (zacatek2 > konec2) {
        std::swap(zacatek2, konec2);
    }
    
    if (konec1 < zacatek2 || konec2 < zacatek1) {
        return 0;
    }
    
    *vysl_zacatek = std::max(zacatek1, zacatek2);
    *vysl_konec = std::min(konec1, konec2);
    return 1;
}
