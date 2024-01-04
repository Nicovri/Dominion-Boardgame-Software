#pragma once

#include "../cardTypes/Victory.hpp"
#include "../enums.hpp"

// Classe des cartes Domaine, sous-classe de Victory.
class Estate: public Victory {

public:
    Estate();
    void play(Board &b);
    void setVictoryPoints(Board &b);
};