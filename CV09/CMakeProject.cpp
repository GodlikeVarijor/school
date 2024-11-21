/*
TODO:
Vytvořte funkci, která porovná dva vektory podle jejich velikosti. Jako výsledek bude vracet
celočíselnou hodnotu +1 (pro |u| > |v|), 0 (pro |u| = |v|) nebo -1 (pro |u| < |v|).
*/

#include <iostream>
#include "VectorMath.h"

int main() {
    vector3d u, v;
    int operaceTyp;

    std::cout << "prvni vektor (x, y, z): ";
    std::cin >> u.x >> u.y >> u.z;

    std::cout << "druhy vektor (x, y, z): ";
    std::cin >> v.x >> v.y >> v.z;

    std::cout << "vyber operaci (1=soucet, 2=skalarniSoucin, 3=vektorovySoucin): ";
    std::cin >> operaceTyp;

    vector3d vysledek;
    switch (operaceTyp) {
        case soucet:
            vysledek = operace(u, v, soucet);
            break;
        case skalarniSoucin:
            vysledek = operace(u, v, skalarniSoucin);
            break;
        case vektorovySoucin:
            vysledek = operace(u, v, vektorovySoucin);
            break;
        default:
            std::cerr << "Neplatna operace" << std::endl;
            return 1;
    }

    tisk(vysledek);
    
    int porovnani = porovnaniVektoru(u, v);
    if (porovnani == 1) {
        std::cout << "prvni vektor je vetsi" << std::endl;
    } else if (porovnani == -1) {
        std::cout << "druhy vektor je vetsi" << std::endl;
    } else {
        std::cout << "oba vektory jsou stejne velke" << std::endl;
    }


    return 0;
}

