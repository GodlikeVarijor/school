#include "point.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "snake.h"
#include "score.h"
#include "obstacles.h"

int main() {
    char player_name[50];

    printf("Enter your name: ");
    fgets(player_name, sizeof(player_name), stdin);

    size_t len = strlen(player_name);
    if (len > 0 && player_name[len - 1] == '\n') {
        player_name[len - 1] = '\0';
    }

    Snake snake;
    int game_over = 0;

    enable_raw_mode();
    initialize_game(&snake);

    while (!game_over) {
        clear_screen();
        draw(&snake);
        update_game(&snake, &game_over);
        usleep(snake.speed * 50000);  
    }

    disable_raw_mode(); 
    save_score(player_name, snake.length);
    printf("Game Over!\n");

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("Do you want to see the top scores? (y/n): ");
    char choice = getchar();
    if (choice == 'y' || choice == 'Y') {
        load_scores();
    }

    return 0;
}
