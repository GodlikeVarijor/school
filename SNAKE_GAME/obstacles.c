#include "point.h"
#include <stdio.h>
#include "obstacles.h"

void load_obstacles(const char* filename, Obstacles* obstacles) {
    FILE* file = fopen(filename, "r");
    if (file) {
        obstacles->count = 0;
        while (fscanf(file, "%d %d", &obstacles->obstacles[obstacles->count].x, &obstacles->obstacles[obstacles->count].y) != EOF) {
            obstacles->count++;
        }
        fclose(file);
    }
}
