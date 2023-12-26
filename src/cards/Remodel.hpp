#pragma once

#include "../cardTypes/Action.hpp"

class Remodel: public Action {

public:
    Remodel();
    void play(Board &b);
    bool useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand);
};