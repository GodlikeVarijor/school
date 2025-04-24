/*
TODO:
Vytvořte konzolovou aplikaci (dle šablony „CMake Project“), která načte textový soubor
D:\vstup.txt a spočítá v něm počet písmen a počet číslic.
Pro vývoj můžete použít následující text, který vložíte do vstupního souboru vstup.txt:
Jako priklad jsou zde cislice 123456, pismena a i jine znaky, jako jsou
konce radku, 3 carky a tecky.
2. Výsledky pak vytiskněte na obrazovku a také uložte do souboru D:\vysledky.txt.
3. statistika souboru (kde se nachazi) a co obsahuje
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <filesystem>

int main()
{
    std::ifstream file("vstup.txt");
    if (!file.is_open())
    {
        std::cerr << "Soubor se nepodarilo otevrit" << std::endl;
        return 1;
    }

    int letters = 0;
    int digits = 0;
    int totalChars = 0;
    int words = 0;
    int sentences = 0;
    bool inWord = false;
    char c;

    while (file.get(c))
    {
        totalChars++;
        if (std::isalpha(c))
        {
            letters++;
            inWord = true;
        }
        else if (std::isdigit(c))
        {
            digits++;
            inWord = true;
        }
        else if (std::isspace(c) || std::isspace(c))
        {
            if (inWord)
            {
                words++;
                inWord = false;
            }       
        }
        else if (c == '.')
        {
            if (inWord)
            {
                words++;
                inWord = false;
            }
            sentences++;
        }
    }

    if (inWord)
    {
        words++;
    }

    std::cout << "Pocet pismen: " << letters << std::endl;
    std::cout << "Pocet cisel: " << digits << std::endl;
    std::cout << "Celkovy pocet znaku: " << totalChars << std::endl;
    std::cout << "Cesta souboru: " << std::filesystem::current_path() << std::endl;
    std::cout << "Pocet slov: " << words << std::endl;
    std::cout << "Pocet vet: " << sentences << std::endl;

    file.clear();
    file.seekg(0);

    std::cout << "Obsah souboru: " << std::endl;
    while (file.get(c))
    {
        std::cout << c;
    }
    std::ofstream output("vysledky.txt");

    if (!output.is_open())
    {
        std::cerr << "Soubor se nepodarilo otevrit" << std::endl;
        return 1;
    }

    output << "Pocet pismen: " << letters << std::endl;
    output << "Pocet cisel: " << digits << std::endl;
    output << "Celkovy pocet znaku: " << totalChars << std::endl;
    output << "Cesta souboru: " << std::filesystem::current_path() << std::endl;
    output << "Pocet slov: " << words << std::endl;
    output << "Pocet vet: " << sentences << std::endl;

    return 0;
}

