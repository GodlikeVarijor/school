#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include "snake.h"

int main() {
    Snake snake;
    int game_over = 0;

    enable_raw_mode(); 
    initialize_game(&snake);

    while (!game_over) {
        clear_screen();
        draw(&snake);
        update_game(&snake, &game_over);
        usleep(snake.speed * 100000); 
    }

    disable_raw_mode(); 
    return 0;
}

