#pragma once

#include "../cardTypes/Action.hpp"
#include "../enums.hpp"
#include <iostream>

// Classe des cartes Chapelle, sous-classe de Action.
class Chapel: public Action {

public:
    Chapel();
    void play(Board &b);
    bool useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand);
};