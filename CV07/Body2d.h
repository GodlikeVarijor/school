#include <iostream>
#include <math.h>
#include <float.h>

#pragma once
int indexNejblizsi(int velikost, int (*poleBodu)[2], int referencniX, int referencniY);
double prumernaVzdalenost(int velikost, int (*poleBodu)[2], int referencniX, int referencniY);
void VypisBlizkyBody(int velikost, int (*poleBodu)[2], int referencniX, int referencniY, double maxVzdalenost);