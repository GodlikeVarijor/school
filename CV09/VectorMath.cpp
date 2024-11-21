/*
TODO:
Vytvořte funkci, která porovná dva vektory podle jejich velikosti. Jako výsledek bude vracet
celočíselnou hodnotu +1 (pro |u| > |v|), 0 (pro |u| = |v|) nebo -1 (pro |u| < |v|).
*/

#include "VectorMath.h"

vector3d operace(vector3d u, vector3d v, typOperace typ) {
    vector3d vysledek;
    switch (typ) {
        case soucet:
            vysledek = {u.x + v.x, u.y + v.y, u.z + v.z};
            break;
        case skalarniSoucin:
            vysledek = {u.x * v.x + u.y * v.y + u.z * v.z, 0, 0};
            break;
        case vektorovySoucin:
            vysledek = {u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x};
            break;
    }
    return vysledek;
}

void tisk(vector3d u) {
    double velikost = std::sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
    std::cout << "w = (" << u.x << ", " << u.y << ", " << u.z << ")\n";
    std::cout << "|w| = " << velikost << "\n";
}

int porovnaniVektoru(vector3d u, vector3d v) {
    double velikostU = std::sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
    double velikostV = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (velikostU > velikostV) {
        return 1;
    } else if (velikostU < velikostV) {
        return -1;
    } else {
        return 0;
    }
}