#ifndef OBSTACLES_H
#define OBSTACLES_H

#include "point.h"

extern int WIDTH;
extern int HEIGHT; 

typedef struct {
    Point obstacles[100];
    int count;            
} Obstacles;

void load_obstacles(const char* filename, Obstacles* obstacles);

#endif
