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