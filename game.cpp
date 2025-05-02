#include "game.h"
#include "game_exceptions.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <limits>
#include <random>

SingleNBackGame::SingleNBackGame(int lvl, int rnds) : level(lvl), score(0), rounds(rnds), currentStreak(0), bestStreak(0) {
    if (level < 1 || level > 5) {
        throw InvalidLevelException();
    }
    generateSequence(rounds + level);
}

void SingleNBackGame::generateSequence(int length) {
    sequence.clear();
    static std::random_device rd;
    static std::mt19937 gen(rd());

    for (int i = 0; i < length; ++i) {
        sequence.push_back(std::make_shared<VisualStimulus>(VisualStimulus::generateRandom()));
    }
}

void SingleNBackGame::play() {
    clearScreen();
    std::cout << "Pregatire...\n\n";

    // Afișează matricea inițială cu toate pătratele albe
    std::vector<std::vector<std::string>> initialGrid(3, std::vector<std::string>(3, "⬜"));
    displayGrid(initialGrid);
    std::cout << "\nTasteaza 1 daca patratul negru este in aceeasi pozitie ca acum " << level << " pasi, altfel 0.\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));

    for (size_t i = 0; i < sequence.size(); ++i) {
        clearScreen();

        // Afișează informații despre joc
        std::cout << "Nivel: " << level << "-Back | Scor: " << score << " | Streak: " << currentStreak << " (Best: " << bestStreak << ")\n\n";

        // Creează și afișează grila curentă
        std::vector<std::vector<std::string>> grid(3, std::vector<std::string>(3, "⬜"));
        sequence[i]->display(grid);
        displayGrid(grid);

        // Dacă suntem după nivelul de start, cere input
        if (i >= level) {
            bool correctAnswer = sequence[i]->matches(sequence[i - level]);

            std::cout << "\nIntrodu raspunsul (1/0): ";

            // Așteaptă input pentru 5 secunde
            auto start = std::chrono::steady_clock::now();
            int userInput = -1;

            while (std::chrono::steady_clock::now() - start < std::chrono::seconds(5)) {
                if (std::cin.peek() != EOF) {
                    std::cin >> userInput;
                    if (userInput == 0 || userInput == 1) {
                        break;
                    }
                    else {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "\nInput invalid. Introdu doar 1 sau 0: ";
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }

            // Verifică răspunsul
            if (userInput == 0 || userInput == 1) {
                if ((userInput == 1 && correctAnswer) || (userInput == 0 && !correctAnswer)) {
                    score++;
                    currentStreak++;
                    if (currentStreak > bestStreak)
                        bestStreak = currentStreak;
                    std::cout << "\nCORECT! (+1 punct)";
                }
                else {
                    currentStreak = 0;
                    std::cout << "\nGRESIT!";
                }
                std::cout << " Scor: " << score << " | Streak: " << currentStreak << "\n";
            }
            else {
                currentStreak = 0;
                std::cout << "\nTimp expirat! Scor: " << score << " | Streak: " << currentStreak << "\n";
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        else {
            std::cout << "\nJocul incepe in curand...\n";
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }

    throw GameOverException(score);
}

int SingleNBackGame::getScore() const { 
    return score; 
}

int SingleNBackGame::getLevel() const { 
    return level; 
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void displayGrid(const std::vector<std::vector<std::string>>& grid) {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            std::cout << cell;
        }
        std::cout << "\n";
    }
}