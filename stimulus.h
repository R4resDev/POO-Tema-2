#ifndef STIMULUS_H
#define STIMULUS_H

#include <memory>
#include <vector>
#include <string>

enum class GameType {
    NORMAL,
    COLOR,
    NUMBER
};

class Stimulus {
public:
    virtual ~Stimulus() = default;
    virtual void display(std::vector<std::vector<std::string>>& grid) const = 0;
    virtual bool matches(const std::shared_ptr<Stimulus>& other) const = 0;
    virtual std::shared_ptr<Stimulus> clone() const = 0;
    virtual void executeDisplay(std::vector<std::vector<std::string>>& grid) const {
        display(grid);
    }
};

class VisualStimulus : public Stimulus {
    int position;
public:
    explicit VisualStimulus(int pos);
    VisualStimulus(const VisualStimulus& other) = default;
    VisualStimulus& operator=(VisualStimulus other);
    
    void display(std::vector<std::vector<std::string>>& grid) const override;
    bool matches(const std::shared_ptr<Stimulus>& other) const override;
    std::shared_ptr<Stimulus> clone() const override;
    
    static VisualStimulus generateRandom();
    friend void swap(VisualStimulus& first, VisualStimulus& second) noexcept;
};

class ColorStimulus : public Stimulus {
    int position;
    std::string color;
public:
    ColorStimulus(int pos, const std::string& col);
    ColorStimulus(const ColorStimulus& other) = default;
    ColorStimulus& operator=(ColorStimulus other);
    
    void display(std::vector<std::vector<std::string>>& grid) const override;
    bool matches(const std::shared_ptr<Stimulus>& other) const override;
    std::shared_ptr<Stimulus> clone() const override;
    
    static ColorStimulus generateRandom();
    friend void swap(ColorStimulus& first, ColorStimulus& second) noexcept;
};

class NumberStimulus : public Stimulus {
    int position;
    int number;
public:
    NumberStimulus(int pos, int num);
    NumberStimulus(const NumberStimulus& other) = default;
    NumberStimulus& operator=(NumberStimulus other);
    
    void display(std::vector<std::vector<std::string>>& grid) const override;
    bool matches(const std::shared_ptr<Stimulus>& other) const override;
    std::shared_ptr<Stimulus> clone() const override;
    
    static NumberStimulus generateRandom();
    friend void swap(NumberStimulus& first, NumberStimulus& second) noexcept;
};

#endif // STIMULUS_H
