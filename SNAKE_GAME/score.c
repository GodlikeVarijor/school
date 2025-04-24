#include "score.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktura pro zaznam skore
typedef struct {
    char name[50];
    int score;
} ScoreEntry;

// Pomocna funkce pro razeni skore
int compare_scores(const void* a, const void* b) {
    return ((ScoreEntry*)b)->score - ((ScoreEntry*)a)->score;
}

// Ulozi skore do souboru, seradi ho a ulozi zpet
void save_score(const char* name, int score) {
    FILE* file = fopen("scores.txt", "r");
    ScoreEntry scores[100];
    int count = 0;

    // Nacteni existujiciho skore
    if (file) {
        while (fscanf(file, "%s %d", scores[count].name, &scores[count].score) != EOF && count < 100) {
            count++;
        }
        fclose(file);
    }

    // Pridani noveho skore
    if (count < 100) {
        strncpy(scores[count].name, name, sizeof(scores[count].name) - 1);
        scores[count].name[sizeof(scores[count].name) - 1] = '\0';
        scores[count].score = score;
        count++;
    }

    // Serazeni skore
    qsort(scores, count, sizeof(ScoreEntry), compare_scores);

    // Prepsani souboru serazenym skore
    file = fopen("scores.txt", "w");
    if (file) {
        for (int i = 0; i < count; i++) {
            fprintf(file, "%s %d\n", scores[i].name, scores[i].score);
        }
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
        while (fscanf(file, "%s %d", name, &score) != EOF) {
            printf("%s %d\n", name, score);
        }
        fclose(file);
    } else {
        printf("No scores available.\n");
    }
}
