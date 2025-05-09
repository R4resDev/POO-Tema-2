#include "utils.h"
#include "game.h"
#include "exceptions.h"
#include <iostream>
#include <cstdlib>
#include <limits>

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
            std::cout << cell << " ";
        }
        std::cout << "\n";
    }
}

void displayMenu() {
    clearScreen();
    std::cout << "=================================\n";
    std::cout << "          SINGLE N-BACK          \n";
    std::cout << "=================================\n";
    std::cout << "1. Joc normal (patrate negre)\n";
    std::cout << "2. Joc color (emoji colorate)\n";
    std::cout << "3. Joc numeric (cifre)\n";
    std::cout << "4. Iesire\n";
    std::cout << "=================================\n";
    std::cout << "Alege optiunea (1-4): ";
}

void displayAfterGameMenu() {
    std::cout << "\n=================================\n";
    std::cout << "1. Joaca din nou acelasi mod\n";
    std::cout << "2. Intoarcere la meniul principal\n";
    std::cout << "=================================\n";
    std::cout << "Alege optiunea (1-2): ";
}

void playGame(int gameType) {
    int level, rounds;
    
    std::cout << "\nIntrodu nivelul (1-5): ";
    std::cin >> level;

    if (level < 1 || level > 5) throw InvalidLevelException();

    std::cout << "Introdu numarul de runde: ";
    std::cin >> rounds;

    GameType type;
    switch (gameType) {
        case 1: type = GameType::NORMAL; break;
        case 2: type = GameType::COLOR; break;
        case 3: type = GameType::NUMBER; break;
        default: throw InvalidGameTypeException();
    }

    while (true) {
        try {
            SingleNBackGame game(level, rounds, type);
            game.play();
        }
        catch (const GameOverException& e) {
            std::cout << e.what() << e.score << std::endl;
        }

        displayAfterGameMenu();
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            continue;
        }
        else if (choice == 2) {
            break;
        }
        else {
            throw InvalidChoiceException();
        }
    }
}