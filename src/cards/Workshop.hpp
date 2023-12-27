#pragma once

#include "../cardTypes/Action.hpp"
#include "../enums.hpp"

// Classe des cartes Atelier, sous-classe de Action.
class Workshop: public Action {

public:
    Workshop();
    void play(Board &b);
    bool useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand);
};