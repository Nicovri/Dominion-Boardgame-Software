#pragma once

#include "../cardTypes/Action.hpp"

class Mine: public Action {

public:
    Mine();
    void play(Board &b);
    bool useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand);
};