#pragma once

#include "../cardTypes/Treasure.hpp"
#include "../enums.hpp"

// Classe des cartes Or, sous-classe de Treasure.
class Gold: public Treasure {

public:
    Gold();
    void play(Board &b);
};