#include "xklimam00.h"
#include <iostream>

int main() {
    struct Interval {
        double zacatek;
        double konec;
    };
    
    struct TestCase {
        Interval interval1;
        Interval interval2;
    };
    
    TestCase testCases[] = {
        {{1.5, 2.8}, {1.6, 2.0}},
        {{1.5, 2.8}, {3.6, 7.5}},
        {{1.5, 4.8}, {2.6, 7.5}},
        {{5.1, -2.3}, {1.5, 6.2}},
        {{2.5, 8.8}, {-0.3, 9.5}},
        {{5.5, -9.5}, {9.9, -2.3}}
    };
    
    double zacatek1, konec1, zacatek2, konec2, vysl_zacatek, vysl_konec;

    for (const auto& testCase : testCases) {
        double zacatek1 = testCase.interval1.zacatek;
        double konec1 = testCase.interval1.konec;
        double zacatek2 = testCase.interval2.zacatek;
        double konec2 = testCase.interval2.konec;
        double vysl_zacatek, vysl_konec;

        std::cout << "(" << zacatek1 << ", " << konec1 << ") and ("
                  << zacatek2 << ", " << konec2 << "): ";

        if (prunik(zacatek1, konec1, zacatek2, konec2, &vysl_zacatek, &vysl_konec)) {
            std::cout << "prunik: (" << vysl_zacatek << ", " << vysl_konec << ")\n";
        } else {
            std::cout << "nema prunik\n";
        }
    }
    
    std::cout << "Zadejte interval 1 (zacatek konec): ";
    std::cin >> zacatek1 >> konec1;
    std::cout << "Zadejte interval 2 (zacatek konec): ";
    std::cin >> zacatek2 >> konec2;
    if (prunik(zacatek1, konec1, zacatek2, konec2, &vysl_zacatek, &vysl_konec)) {
        std::cout << "Prunik intervalu: " << vysl_zacatek << " " << vysl_konec << std::endl;
    } else {
        std::cout << "Nema prunik" << std::endl;
    }
    return 0;
}

