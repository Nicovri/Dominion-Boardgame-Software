#pragma once

#include "../cardTypes/Action.hpp"

class Village: public Action {

public:
    Village();
    void play(Board &b);
    bool useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand);
};