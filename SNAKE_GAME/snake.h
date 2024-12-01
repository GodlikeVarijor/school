#ifndef SNAKE_H
#define SNAKE_H

#include "point.h"
#include "obstacles.h"

#define WIDTH 40   
#define HEIGHT 20  

typedef struct {
    Point body[100]; 
    int length;      
    Point food;      
    int speed;       
    char direction;  
} Snake;

void clear_screen();
void draw(const Snake* snake, const Obstacles* obstacles);
void initialize_game(Snake* snake);
void update_game(Snake* snake, int* game_over, const Obstacles* obstacles);
void generate_food(Snake* snake);
void enable_raw_mode();
void disable_raw_mode();
int kbhit();    

#endif
