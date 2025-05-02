#include "stimulus.h"
#include <vector>
#include <memory>

class SingleNBackGame {
    int level;
    int score;
    int rounds;
    int currentStreak;
    int bestStreak;
    std::vector<std::shared_ptr<Stimulus>> sequence;

    void generateSequence(int length);
    
public:
    SingleNBackGame(int lvl, int rnds);
    void play();
    int getScore() const;
    int getLevel() const;
};

void clearScreen();
void displayGrid(const std::vector<std::vector<std::string>>& grid);