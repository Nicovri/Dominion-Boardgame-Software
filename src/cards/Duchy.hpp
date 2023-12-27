#pragma once

#include "../cardTypes/Victory.hpp"
#include "../enums.hpp"

// Classe des cartes Duché, sous-classe de Victory.
class Duchy: public Victory {

public:
    Duchy();
    void play(Board &b);
};