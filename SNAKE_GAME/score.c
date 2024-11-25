#include <stdio.h>
#include "score.h"

void save_score(int score) {
    FILE* file = fopen("scores.txt", "a");
    if (file) {
        fprintf(file, "%d\n", score);
        fclose(file);
    }
}

void load_scores() {
    FILE* file = fopen("scores.txt", "r");
    if (file) {
        int score;
        printf("Top Scores:\n");
        while (fscanf(file, "%d", &score) != EOF) {
            printf("%d\n", score);
        }
        fclose(file);
    } else {
        printf("No scores available.\n");
    }
}
