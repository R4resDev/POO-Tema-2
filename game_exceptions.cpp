#include "game_exceptions.h"

const char* InvalidLevelException::what() const noexcept {
    return "Nivel invalid! Nivelul trebuie sa fie intre 1 si 5.";
}

const char* InvalidInputException::what() const noexcept {
    return "Input invalid! Introduceti doar 1 sau 0.";
}

GameOverException::GameOverException(int s) : score(s) {}

const char* GameOverException::what() const noexcept {
    return "Jocul s-a terminat! Scorul dumneavoastra este: ";
}