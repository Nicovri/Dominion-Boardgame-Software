#pragma once

#include "../cardTypes/Victory.hpp"
#include "../enums.hpp"

// Classe des cartes Jardins, sous-classe de Victory.
class Gardens: public Victory {

public:
    Gardens();
    void play(Board &b);
};