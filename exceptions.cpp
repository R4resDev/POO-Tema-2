#include "exceptions.h"

const char* InvalidLevelException::what() const noexcept {
    return "Nivel invalid! Nivelul trebuie sa fie intre 1 si 5.";
}

const char* InvalidInputException::what() const noexcept {
    return "Input invalid! Introduceti doar 1 sau 0.";
}

const char* InvalidGameTypeException::what() const noexcept {
    return "Tip de joc invalid! Alegeti intre 1, 2 sau 3.";
}

const char* InvalidChoiceException::what() const noexcept {
    return "Optiune invalida! Alegeti 1 sau 2.";
}
const char* GameOverException::what() const noexcept {
    return "Joc terminat! Scor final: ";
}
