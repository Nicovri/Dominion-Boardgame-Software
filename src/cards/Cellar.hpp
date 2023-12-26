#pragma once

#include "../cardTypes/Action.hpp"
#include <iostream>

class Cellar: public Action {

public:
    Cellar();
    void play(Board &b);
    bool useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand);
};