#include "stimulus.h"
#include "exceptions.h"
#include <random>
#include <algorithm>

// VisualStimulus implementation
VisualStimulus::VisualStimulus(int pos) : position(pos) {
    if (pos < 1 || pos > 9) throw InvalidInputException();
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

void swap(VisualStimulus& first, VisualStimulus& second) noexcept {
    using std::swap;
    swap(first.position, second.position);
}

// ColorStimulus implementation
ColorStimulus::ColorStimulus(int pos, const std::string& col) : position(pos), color(col) {
    if (pos < 1 || pos > 9) throw InvalidInputException();
}

void ColorStimulus::display(std::vector<std::vector<std::string>>& grid) const {
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;
    grid[row][col] = color;
}

bool ColorStimulus::matches(const std::shared_ptr<Stimulus>& other) const {
    auto derived = std::dynamic_pointer_cast<ColorStimulus>(other);
    if (!derived) return false;
    return position == derived->position && color == derived->color;
}

std::shared_ptr<Stimulus> ColorStimulus::clone() const {
    return std::make_shared<ColorStimulus>(*this);
}

ColorStimulus ColorStimulus::generateRandom() {
    static std::vector<std::string> colors = {"🔴", "🟢", "🔵", "🟡"};
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> pos_dist(1, 9);
    std::uniform_int_distribution<> col_dist(0, colors.size()-1);
    return ColorStimulus(pos_dist(gen), colors[col_dist(gen)]);
}

void swap(ColorStimulus& first, ColorStimulus& second) noexcept {
    using std::swap;
    swap(first.position, second.position);
    swap(first.color, second.color);
}

// NumberStimulus implementation
NumberStimulus::NumberStimulus(int pos, int num) : position(pos), number(num) {
    if (pos < 1 || pos > 9 || num < 0 || num > 9) throw InvalidInputException();
}

void NumberStimulus::display(std::vector<std::vector<std::string>>& grid) const {
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;
    grid[row][col] = std::to_string(number);
}

bool NumberStimulus::matches(const std::shared_ptr<Stimulus>& other) const {
    auto derived = std::dynamic_pointer_cast<NumberStimulus>(other);
    if (!derived) return false;
    return position == derived->position && number == derived->number;
}

std::shared_ptr<Stimulus> NumberStimulus::clone() const {
    return std::make_shared<NumberStimulus>(*this);
}

NumberStimulus NumberStimulus::generateRandom() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> pos_dist(1, 9);
    std::uniform_int_distribution<> num_dist(0, 9);
    return NumberStimulus(pos_dist(gen), num_dist(gen));
}

void swap(NumberStimulus& first, NumberStimulus& second) noexcept {
    using std::swap;
    swap(first.position, second.position);
    swap(first.number, second.number);
}
