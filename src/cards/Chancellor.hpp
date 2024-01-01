#pragma once

#include "../cardTypes/Action.hpp"
#include "../enums.hpp"
#include <iostream>

// Classe des cartes Chancelier, sous-classe de Action.
class Chancellor: public Action {

public:
    Chancellor();
    void play(Board &b);
    bool useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand);
};