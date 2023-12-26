#pragma once

#include "../cardTypes/Action.hpp"

class Market: public Action {

public:
    Market();
    void play(Board &b);
    bool useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand);
};