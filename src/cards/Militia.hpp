#pragma once

#include "../cardTypes/Action.hpp"
#include "../enums.hpp"
#include <iostream>

// Classe des cartes Milice, sous-classe de Action.
class Militia: public Action {

public:
    Militia();
    void play(Board &b);
    bool useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand);
};