#include "stimulus.h"
#include "game_exceptions.h"
#include <random>

VisualStimulus::VisualStimulus(int pos) : position(pos) {
    if (pos < 1 || pos > 9) {
        throw InvalidInputException();
    }
}

void VisualStimulus::display(std::vector<std::vector<std::string>>& grid) const {
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;
    grid[row][col] = "⬛";
}

bool VisualStimulus::matches(const std::shared_ptr<Stimulus>& other) const {
    auto derived = std::dynamic_pointer_cast<VisualStimulus>(other);
    if (!derived) return false;
    return position == derived->position;
}

std::shared_ptr<Stimulus> VisualStimulus::clone() const {
    return std::make_shared<VisualStimulus>(*this);
}

VisualStimulus VisualStimulus::generateRandom() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 9);
    return VisualStimulus(dist(gen));
}