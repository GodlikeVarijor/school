#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static vector2 head;
static vector2 food;
static vector2 screen = {MAX_WIDTH, MAX_HEIGHT};
static vector2 dir;
static int score;
static bool running;

void initialize_game() {
    head.x = screen.x / 2;
    head.y = screen.y / 2;
    food.x = rand() % screen.x;
    food.y = rand() % screen.y;
    dir.x = 1;
    dir.y = 0;
    score = 0;
    running = true;
}

bool collide(vector2 a, vector2 b) {
    return a.x == b.x && a.y == b.y;
}

void update() {
    vector2 next = {head.x + dir.x, head.y + dir.y};

    if (collide(next, food)) {
        score++;
        head = next;
        food.x = rand() % screen.x;
        food.y = rand() % screen.y;
    } else {
        for (int i = score; i > 0; i--) {
            if (collide(next, head)) {
                running = false;
                break;
            }
        }
        head = next;
    }

    if (head.x < 0 || head.x >= screen.x || head.y < 0 || head.y >= screen.y) {
        running = false;
    }
}

void render() {
    system("clear");
    for (int y = 0; y < screen.y; y++) {
        for (int x = 0; x < screen.x; x++ ) {
            if (collide(head, (vector2) {x, y})) {
                printf("0");
            } else if (collide(food, (vector2) {x, y})) {
                printf("X");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}