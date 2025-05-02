#include "game.h"
#include "game_exceptions.h"
#include <iostream>

int main() {
    try {
        int level, rounds;

        std::cout << "Bine ai venit la Single n-Back!\n";
        std::cout << "Introdu nivelul (1-5): ";
        std::cin >> level;

        if (level < 1 || level > 5) {
            throw InvalidLevelException();
        }

        std::cout << "Introdu numarul de runde: ";
        std::cin >> rounds;

        SingleNBackGame game(level, rounds);
        game.play();
    }
    catch (const InvalidLevelException& e) {
        std::cerr << "Eroare: " << e.what() << std::endl;
        return 1;
    }
    catch (const InvalidInputException& e) {
        std::cerr << "Eroare: " << e.what() << std::endl;
        return 1;
    }
    catch (const GameOverException& e) {
        std::cout << e.what() << e.score << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Eroare neasteptata: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}