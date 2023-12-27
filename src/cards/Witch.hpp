#pragma once

#include "../cardTypes/Action.hpp"
#include "../enums.hpp"

// Classe des cartes Sorcière, sous-classe de Action.
class Witch: public Action {

public:
    Witch();
    void play(Board &b);
    bool useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand);
};