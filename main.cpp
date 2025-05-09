#include "game.h"
#include "exceptions.h"
#include "utils.h"
#include <iostream>
#include <limits>

int main() {
    while (true) {
        try {
            displayMenu();
            int choice;
            std::cin >> choice;

            if (choice == 4) {
                break;
            }
            else if (choice >= 1 && choice <= 3) {
                playGame(choice);
            }
            else {
                throw InvalidGameTypeException();
            }
        }
        catch (const InvalidLevelException& e) {
            std::cerr << "Eroare: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        catch (const InvalidInputException& e) {
            std::cerr << "Eroare: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        catch (const InvalidGameTypeException& e) {
            std::cerr << "Eroare: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        catch (const InvalidChoiceException& e) {
            std::cerr << "Eroare: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        catch (const std::exception& e) {
            std::cerr << "Eroare neasteptata: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return 0;
}
