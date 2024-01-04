#pragma once

#include "../cardTypes/Victory.hpp"
#include "../enums.hpp"

// Classe des cartes Malédiction, sous-classe de Victory.
class Curse: public Victory {

public:
    Curse();
    void play(Board &b);
    void setVictoryPoints(Board &b);
};