#include <memory>
#include <vector>
#include <string>

class Stimulus {
public:
    virtual ~Stimulus() = default;
    virtual void display(std::vector<std::vector<std::string>>& grid) const = 0;
    virtual bool matches(const std::shared_ptr<Stimulus>& other) const = 0;
    virtual std::shared_ptr<Stimulus> clone() const = 0;
};

class VisualStimulus : public Stimulus {
    int position;
public:
    explicit VisualStimulus(int pos);
    void display(std::vector<std::vector<std::string>>& grid) const override;
    bool matches(const std::shared_ptr<Stimulus>& other) const override;
    std::shared_ptr<Stimulus> clone() const override;
    static VisualStimulus generateRandom();
};