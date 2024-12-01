#include "point.h"
#include <stdio.h>
#include "obstacles.h"

void load_obstacles(const char* filename, Obstacles* obstacles) {
    FILE* file = fopen(filename, "r");
    if (file) {
        obstacles->count = 0;
        while (fscanf(file, "%d %d", &obstacles->obstacles[obstacles->count].x, &obstacles->obstacles[obstacles->count].y) != EOF) {
            printf("Loaded obstacle at (%d, %d)\n", obstacles->obstacles[obstacles->count].x, obstacles->obstacles[obstacles->count].y);
            obstacles->count++;
        }
        fclose(file);
    } else {
        printf("Could not open obstacles file.\n");
    }
}

