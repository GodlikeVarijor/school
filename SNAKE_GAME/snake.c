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
    Obstacles obstacles;

    // Nacteni velikosti hraciho pole ze souboru
    FILE* field_file = fopen("field_size.txt", "r");
    if (field_file) {
        fscanf(field_file, "%d %d", &WIDTH, &HEIGHT);
        fclose(field_file);
    }

    // Ziskani jmena hrace
    printf("Enter your name: ");
    fgets(player_name, sizeof(player_name), stdin);

    size_t len = strlen(player_name);
    if (len > 0 && player_name[len - 1] == '\n') {
        player_name[len - 1] = '\0';
    }

    Snake snake;
    int game_over = 0;

    // Nacteni prekazek ze souboru
    load_obstacles("obstacles.txt", &obstacles);

    // Povoleni raw rezimu
    enable_raw_mode();
    // Inicializace hry
    initialize_game(&snake);

    // Hlavni herni smycka
    while (!game_over) {
        clear_screen();
        draw(&snake, &obstacles);  
        update_game(&snake, &game_over, &obstacles); 
        usleep(snake.speed * 50000);  
    }

    // Zakazani raw rezimu
    disable_raw_mode(); 
    // Ulozeni skore
    save_score(player_name, snake.length);
    printf("Game Over!\n");

    // Cekani na stisk klavesy
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    // Dotaz na zobrazeni top skore
    printf("Do you want to see the top scores? (y/n): ");
    char choice = getchar();
    if (choice == 'y' || choice == 'Y') {
        load_scores();
    }

    return 0;
}