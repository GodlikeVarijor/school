#include <iostream>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

void pismenofunkce(char* text) {
    int count = 0;
    for (int i = 0; i < strlen(text); i++) {            // strlen vrati delku retezce (projde kazdy znak v textu)
        if (isalpha(text[i])) {                         // pokud je znak pismeno, vypise ho
            count++;
        }
    }
    std::cout << "Pocet pismen: " << count << std::endl;
}

void cislofunkce(char* text) {
    int count = 0;
    for (int i = 0; i < strlen(text); i++) {            // strlen vrati delku retezce (projde kazdy znak v textu)
        if (isdigit(text[i])) {                         // pokud je znak cislo, vypise ho
            count++;
        }
    }
    std::cout << "Pocet cisel: " << count << std::endl;
}

void znakyfunkce(char* text) {
    int count = 0;
    for (int i = 0; i < strlen(text); i++) {            // strlen vrati delku retezce (projde kazdy znak v textu)
        if (isalnum(text[i])) {                         // pokud je znak pismeno nebo cislo, vypise ho
            count++;
        }
    }
    std::cout << "Pocet znaku: " << count << std::endl;
}

void maxDelkaSlova(char* text) {
    int count = 0;
    int max = 0;
    for (int i = 0; i <= strlen(text); i++) {
        if (isalpha(text[i]) || isdigit(text[i])) {
            count++;
        } else {
            if (count > max) {
                max = count;
            }
            count = 0;
        }
    }
    std::cout << "Nejdelsi slovo ma delku:" << max << std::endl;
}

int main() {
    char text[] = "Toto jsou 2 vzorove vety, ktere budou zpracovavany Vasemi funkcemi. Auto Hyundai ix35 ma pres 120 konskych sil.";
    pismenofunkce(text);
    cislofunkce(text);
    znakyfunkce(text);
    maxDelkaSlova(text);
    return 0;
}

