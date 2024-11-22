/*
TODO:
Vytvořte aplikaci odpovídající hře had (snake) známé z mobilních telefonů NOKIA. Hru bude možné ovládat
skrze směrová tlačítka klávesnice.
Základní parametry programu:
1. Had se bude samostatně pohybovat posledním zadaným směrem.
2. Po každém úspěšně získané položce (snědení jídla) se had zvětší o jeden článek.
3. Bude kontrolováno zda had narazil do sebe samého, poté hra skončí.
4. Hrany konzole budou pro hada neprůchozí.
5. Hra bude obsahovat statistiky nejlepších 10 hráčů, které budou uloženy v externím textovém
souboru.
ADDITIONAL: 
6. Implementujte možnost nahrání překážek do hracího pole z textového souboru
7. Implementujte možnost změny rychlosti hada
8. Implementujte možnost změny velikosti hracího pole
*/


// snake.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "snake.h"
#include "input.h"

#define FRAME_RATE 200

int main() {
    srand(time(NULL));
    initialize_game();
    load_scores();

    while (is_running()) {
        input();
        update();
        render();

        struct timespec ts = {0, FRAME_RATE * 1000000};
        nanosleep(&ts, NULL);
    }

    save_scores();
    printf("\nKonec hry\n");
    return 0;
}
