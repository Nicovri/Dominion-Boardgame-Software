#pragma once

#include "../cardTypes/Action.hpp"
#include "../enums.hpp"
#include <iostream>

// Classe des cartes Comptoir, sous-classe de Action.
class TradingPost: public Action {

public:
    TradingPost();
    void play(Board &b);
    bool useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand);
};