#include <conio.h>
#include "snake.h"

void input() {
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
            case 'w': dir.x = 0; dir.y = -1; break;
            case 's': dir.x = 0; dir.y = 1; break;
            case 'a': dir.x = -1; dir.y = 0; break;
            case 'd': dir.x = 1; dir.y = 0; break;
        }
    }
}
