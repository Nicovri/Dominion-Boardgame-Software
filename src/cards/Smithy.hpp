#pragma once

#include "../cardTypes/Action.hpp"

class Smithy: public Action {

public:
    Smithy();
    void play(Board &b);
    bool useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand);
};