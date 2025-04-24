#include "Body2d.h"
#include <iostream>

#define POCET_BODU 10

int main() {
int body[POCET_BODU][2] = {5, 10,
-14, 2,
45, 4,
-9, 8,
58, -3,
47, 5,
-18, -86,
75, 7,
-25, 51,
17, 98};


    int referencniX, referencniY;
    double maxVzdalenost;

    std::cout << "Zadejte souradnice referencniho bodu: ";
    std::cin >> referencniX >> referencniY;
    std::cout << "Zadejte maximalni vzdalenost: ";
    std::cin >> maxVzdalenost;

    int index = indexNejblizsi(POCET_BODU, body, referencniX, referencniY);
    double prumer = prumernaVzdalenost(POCET_BODU, body, referencniX, referencniY);

    std::cout << "Nejblizsi bod ma souradnice: " << body[index][0] << ", " << body[index][1] << std::endl;
    std::cout << "Prumerna vzdalenost bodu od referencniho bodu je: " << prumer << std::endl;

    VypisBlizkyBody(POCET_BODU, body, referencniX, referencniY, maxVzdalenost);

    return 0;
}
