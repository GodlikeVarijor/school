    #include <stdbool.h>

    #ifndef SNAKE_H
    #define SNAKE_H

    #define MAX_WIDTH 40
    #define MAX_HEIGHT 20

    typedef struct {
        int x;
        int y;
    } vector2;

    void initialize_game();
    void update();
    void render();
    bool is_running();
    void load_scores();
    void save_scores();


    #endif

