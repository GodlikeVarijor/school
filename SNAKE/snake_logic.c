#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SEGMENTS 1000
static vector2 segments[MAX_SEGMENTS];

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
        food.x = rand() % screen.x;
        food.y = rand() % screen.y;
    } else {

        for (int i = score - 1; i > 0; i--) {
            segments[i] = segments[i - 1];
        }
        if (score > 0) {
            segments[0] = head;
        }
    }

    head = next;

    for (int i = 0; i < score; i++) {
        if (collide(head, segments[i])) {
            running = false;
            return;
        }
    }

    if (head.x < 0 || head.x >= screen.x || head.y < 0 || head.y >= screen.y) {
        running = false;
    }
}


void render() {
    system("clear");
    for (int y = 0; y < screen.y; y++) {
        for (int x = 0; x < screen.x; x++) {
            if (head.x == x && head.y == y) {
                printf("O"); 
            } else if (food.x == x && food.y == y) {
                printf("@"); 
            } else {
                bool is_body = false;
                for (int i = 0; i < score; i++) {
                    if (segments[i].x == x && segments[i].y == y) {
                        is_body = true;
                        break;
                    }
                }
                if (is_body) {
                    printf("o"); 
                } else {
                    printf("."); 
                }
            }
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}
