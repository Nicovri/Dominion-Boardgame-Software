#pragma once

#include "../cardTypes/Treasure.hpp"
#include "../enums.hpp"

// Classe des cartes Argent, sous-classe de Treasure.
class Silver: public Treasure {

public:
    Silver();
    void play(Board &b);
};