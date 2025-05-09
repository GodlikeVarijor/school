#include "point.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "snake.h"
#include "obstacles.h"

int WIDTH = 20;
int HEIGHT = 20;

// Funkce pro vycisteni obrazovky
void clear_screen() {
    printf("\033[H\033[J"); // Escape sequence pro vycisteni obrazovky
}

// Funkce pro vykresleni hada a prekazek
void draw(const Snake* snake, const Obstacles* obstacles) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) {
                printf("#"); 
            } else if (x == snake->food.x && y == snake->food.y) {
                printf("*"); 
            } else {
                int is_body = 0;
                for (int i = 0; i < snake->length; i++) {
                    if (snake->body[i].x == x && snake->body[i].y == y) {
                        printf("O");
                        is_body = 1;
                        break;
                    }
                }

                int is_obstacle = 0;
                for (int i = 0; i < obstacles->count; i++) {
                    if (obstacles->obstacles[i].x == x && obstacles->obstacles[i].y == y) {
                        printf("X");
                        is_obstacle = 1;
                        break;
                    }
                }

                if (!is_body && !is_obstacle) {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}

// Funkce pro inicializaci hry
void initialize_game(Snake* snake) {
    srand(time(NULL));
    snake->length = 1;
    snake->body[0] = (Point){WIDTH / 2, HEIGHT / 2};
    snake->direction = 'w'; 
    snake->speed = 10;      
    generate_food(snake);
}

// Funkce pro generovani jidla
void generate_food(Snake* snake) {
    snake->food.x = rand() % (WIDTH - 2) + 1;
    snake->food.y = rand() % (HEIGHT - 2) + 1;
}

// Funkce pro aktualizaci hry
void update_game(Snake* snake, int* game_over, const Obstacles* obstacles) {
    if (kbhit()) {
        char input = getchar();
        switch (input) {
            case 'w': if (snake->direction != 's') snake->direction = 'w'; break;
            case 's': if (snake->direction != 'w') snake->direction = 's'; break;
            case 'a': if (snake->direction != 'd') snake->direction = 'a'; break;
            case 'd': if (snake->direction != 'a') snake->direction = 'd'; break;
        }
    }

    Point next_head = snake->body[0];
    switch (snake->direction) {
        case 'w': next_head.y--; break;
        case 's': next_head.y++; break;
        case 'a': next_head.x--; break;
        case 'd': next_head.x++; break;
    }
    // Kontrola kolize s okrajem hraciho pole
    if (next_head.x <= 0 || next_head.x >= WIDTH - 1 || next_head.y <= 0 || next_head.y >= HEIGHT - 1) {
        *game_over = 1;
        return;
    }
    // Kontrola kolize s telem hada
    for (int i = 0; i < snake->length; i++) {
        if (snake->body[i].x == next_head.x && snake->body[i].y == next_head.y) {
            *game_over = 1;
            return;
        }
    }
    // Kontrola kolize s prekazkami
    for (int i = 0; i < obstacles->count; i++) {
        if (obstacles->obstacles[i].x == next_head.x && obstacles->obstacles[i].y == next_head.y) {
            *game_over = 1;
            return;
        }
    }
    // Pohyb hada
    for (int i = snake->length; i > 0; i--) {
        snake->body[i] = snake->body[i - 1];
    }
    snake->body[0] = next_head;
    // Kontrola, zda had snedl jidlo
    if (next_head.x == snake->food.x && next_head.y == snake->food.y) {
        snake->length++;
        generate_food(snake);
        if (snake->length % 2 == 0) snake->speed--; 
    } else {
        snake->body[snake->length] = (Point){0, 0};
    }
}

// Funkce pro povoleni raw rezimu
void enable_raw_mode() {
    struct termios term;    // Struktura obsahujici nastaveni terminalu
    tcgetattr(STDIN_FILENO, &term);     // Nacte aktualni nastaveni terminalu
    term.c_lflag &= ~(ICANON | ECHO);   // Vypne okamzity vstup + nezobrazuje zadne znaky
    tcsetattr(STDIN_FILENO, TCSANOW, &term);    // Hned aplikuje zmeny
}

// Funkce pro zakazani raw rezimu
void disable_raw_mode() {
    struct termios term;    
    tcgetattr(STDIN_FILENO, &term);     
    term.c_lflag |= (ICANON | ECHO);    // Zapne okamzity vstup + zobrazi znaky
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Funkce pro zjisteni, zda byla stisknuta klavesa
int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}