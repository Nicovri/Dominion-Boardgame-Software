#pragma once

#include "../cardTypes/Action.hpp"
#include "../enums.hpp"

// Classe des cartes Village Minier, sous-classe de Action.
class MiningVillage: public Action {

public:
    MiningVillage();
    void play(Board &b);
    bool useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand);
};