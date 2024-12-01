#include "point.h"
#include <stdio.h>
#include "obstacles.h"

void load_obstacles(const char* filename, Obstacles* obstacles) {
    FILE* file = fopen(filename, "r");
    if (file) {
        obstacles->count = 0;
        int x, y;
        while (fscanf(file, "%d %d", &x, &y) != EOF) {
            if (x > 0 && x < WIDTH - 1 && y > 0 && y < HEIGHT - 1) {
                obstacles->obstacles[obstacles->count].x = x;
                obstacles->obstacles[obstacles->count].y = y;
                obstacles->count++;
            }
        }
        fclose(file);
    }
}
