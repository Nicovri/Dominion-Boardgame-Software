#pragma once

#include "../cardTypes/Action.hpp"
#include "../enums.hpp"
#include <iostream>

// Classe des cartes Cave, sous-classe de Action.
class Cellar: public Action {

public:
    Cellar();
    void play(Board &b);
    bool useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand);
};