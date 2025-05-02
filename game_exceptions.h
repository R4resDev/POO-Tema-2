#include <exception>
#include <string>

class GameException : public std::exception {
public:
    virtual const char* what() const noexcept override = 0;
    virtual ~GameException() = default;
};

class InvalidLevelException : public GameException {
public:
    const char* what() const noexcept override;
};

class InvalidInputException : public GameException {
public:
    const char* what() const noexcept override;
};

class GameOverException : public GameException {
public:
    const char* what() const noexcept override;
    int score;
    explicit GameOverException(int s);
};