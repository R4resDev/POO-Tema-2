#include "game.h"
#include "stimulus.h"
#include "exceptions.h"
#include "utils.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <random>

int SingleNBackGame::gameCount = 0;

void SingleNBackGame::generateSequence(int length) {
    sequence.clear();
    static std::random_device rd;
    static std::mt19937 gen(rd());

    for (int i = 0; i < length; ++i) {
        switch (gameType) {
            case GameType::NORMAL:
                sequence.push_back(std::make_shared<VisualStimulus>(VisualStimulus::generateRandom()));
                break;
            case GameType::COLOR:
                sequence.push_back(std::make_shared<ColorStimulus>(ColorStimulus::generateRandom()));
                break;
            case GameType::NUMBER:
                sequence.push_back(std::make_shared<NumberStimulus>(NumberStimulus::generateRandom()));
                break;
        }
    }
}

SingleNBackGame::SingleNBackGame(int lvl, int rnds, GameType type) 
    : level(lvl), score(0), rounds(rnds), currentStreak(0), bestStreak(0), gameType(type) {
    if (level < 1 || level > 5) throw InvalidLevelException();
    generateSequence(rounds + level);
    gameCount++;
}

SingleNBackGame::SingleNBackGame(const SingleNBackGame& other) 
    : level(other.level), score(other.score), rounds(other.rounds),
      currentStreak(other.currentStreak), bestStreak(other.bestStreak),
      gameType(other.gameType) {
    for (const auto& stim : other.sequence) {
        sequence.push_back(stim->clone());
    }
    gameCount++;
}

SingleNBackGame& SingleNBackGame::operator=(SingleNBackGame other) {
    swap(*this, other);
    return *this;
}

SingleNBackGame::~SingleNBackGame() {
    gameCount--;
}

void SingleNBackGame::play() {
    clearScreen();
    std::cout << "Pregatire...\n\n";

    std::vector<std::vector<std::string>> initialGrid(3, std::vector<std::string>(3, "⬜"));
    displayGrid(initialGrid);
    
    std::string gameTypeStr;
    switch (gameType) {
        case GameType::NORMAL: gameTypeStr = "normal (patrat negru)"; break;
        case GameType::COLOR: gameTypeStr = "color"; break;
        case GameType::NUMBER: gameTypeStr = "numeric"; break;
    }
    
    std::cout << "\nMod de joc: " << gameTypeStr 
              << "\nTasteaza 1 daca stimulul este la fel ca acum " << level << " pasi, altfel 0.\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));

    for (size_t i = 0; i < sequence.size(); ++i) {
        clearScreen();
        std::cout << "Nivel: " << level << "-Back | Scor: " << score 
                  << " | Streak: " << currentStreak << " (Best: " << bestStreak << ")\n\n";

        std::vector<std::vector<std::string>> grid(3, std::vector<std::string>(3, "⬜"));
        sequence[i]->executeDisplay(grid);
        displayGrid(grid);

        if (i >= static_cast<size_t>(level)) {
            bool correctAnswer = sequence[i]->matches(sequence[i - level]);

            std::cout << "\nIntrodu raspunsul (1/0): ";
            auto start = std::chrono::steady_clock::now();
            int userInput = -1;

            while (std::chrono::steady_clock::now() - start < std::chrono::seconds(5)) {
                if (std::cin.peek() != EOF) {
                    std::cin >> userInput;
                    if (userInput == 0 || userInput == 1) break;
                    else {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "\nInput invalid. Introdu doar 1 sau 0: ";
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }

            if (userInput == 0 || userInput == 1) {
                if ((userInput == 1 && correctAnswer) || (userInput == 0 && !correctAnswer)) {
                    score++;
                    currentStreak++;
                    if (currentStreak > bestStreak) bestStreak = currentStreak;
                    std::cout << "\nCORECT! (+1 punct)";
                } else {
                    currentStreak = 0;
                    std::cout << "\nGRESIT!";
                }
                std::cout << " Scor: " << score << " | Streak: " << currentStreak << "\n";
            } else {
                currentStreak = 0;
                std::cout << "\nTimp expirat! Scor: " << score << " | Streak: " << currentStreak << "\n";
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::this_thread::sleep_for(std::chrono::seconds(2));
        } else {
            std::cout << "\nJocul incepe in curand...\n";
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }

    throw GameOverException(score);
}

void swap(SingleNBackGame& first, SingleNBackGame& second) noexcept {
    using std::swap;
    swap(first.level, second.level);
    swap(first.score, second.score);
    swap(first.rounds, second.rounds);
    swap(first.currentStreak, second.currentStreak);
    swap(first.bestStreak, second.bestStreak);
    swap(first.gameType, second.gameType);
    swap(first.sequence, second.sequence);
}
