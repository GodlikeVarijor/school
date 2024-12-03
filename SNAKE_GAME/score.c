#include "point.h"
#include <stdio.h>
#include "score.h"

// Funkce pro ulozeni skore
void save_score(const char* name, int score) {
    FILE* file = fopen("scores.txt", "a");
    if (file) {
        fprintf(file, "%s %d\n", name, score);
        fclose(file);
    }
}

// Funkce pro nacteni skore
void load_scores() {
    FILE* file = fopen("scores.txt", "r");
    if (file) {
        char name[50];
        int score;
        printf("Top Scores:\n");
        // Cteni skore ze souboru
        while (fscanf(file, "%s %d", name, &score) != EOF) {
            printf("%s %d\n", name, score);
        }
        fclose(file);
    } else {
        printf("No scores available.\n");
    }
}