#include "stimulus.h"
#include <vector>
#include <memory>

class SingleNBackGame {
    int level;
    int score;
    int rounds;
    int currentStreak;
    int bestStreak;
    GameType gameType;
    std::vector<std::shared_ptr<Stimulus>> sequence;
    static int gameCount;

    void generateSequence(int length);
    
public:
    SingleNBackGame(int lvl, int rnds, GameType type);
    SingleNBackGame(const SingleNBackGame& other);
    SingleNBackGame& operator=(SingleNBackGame other);
    ~SingleNBackGame();

    static int getGameCount() { return gameCount; }
    void play();
    
    friend void swap(SingleNBackGame& first, SingleNBackGame& second) noexcept;
};
