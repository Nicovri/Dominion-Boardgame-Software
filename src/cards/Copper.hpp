#pragma once

#include "../cardTypes/Treasure.hpp"
#include "../enums.hpp"

// Classe des cartes Cuivre, sous-classe de Treasure.
class Copper: public Treasure {

public:
    Copper();
    void play(Board &b);
};