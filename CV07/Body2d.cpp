#include "Body2d.h"

int indexNejblizsi(int velikost, int (*poleBodu)[2], int referencniX, int referencniY) {
    double nejmensiVzdalenost = DBL_MAX;
    int index = 0;

    for (int i = 0; i < velikost; i++) {
        double vzdalenost = sqrt(pow(poleBodu[i][0] - referencniX, 2) + pow(poleBodu[i][1] - referencniY, 2));
        if (vzdalenost < nejmensiVzdalenost) {
            nejmensiVzdalenost = vzdalenost;
            index = i;
        }
    }

    return index;
}

double prumernaVzdalenost(int velikost, int (*poleBodu)[2], int referencniX, int referencniY) {
    double prumer = 0;

    for (int i = 0; i < velikost; i++) {
        prumer += sqrt(pow(poleBodu[i][0] - referencniX, 2) + pow(poleBodu[i][1] - referencniY, 2));
    }

    return prumer / velikost;
}

void VypisBlizkyBody(int velikost, int (*poleBodu)[2], int referencniX, int referencniY, double maxVzdalenost) {
    std::cout << "Body blizko referencniho bodu (" << referencniX << ", " << referencniY << ") do vzdalenosti " << maxVzdalenost << ":" << std::endl;
    for (int i = 0; i < velikost; i++) {
        double vzdalenost = sqrt(pow(poleBodu[i][0] - referencniX, 2) + pow(poleBodu[i][1] - referencniY, 2));
        if (vzdalenost <= maxVzdalenost) {
            std::cout << "Bod " << i + 1 << ": (" << poleBodu[i][0] << ", " << poleBodu[i][1] << "), Vzdalenost: " << vzdalenost << std::endl;
        }
    }
}
