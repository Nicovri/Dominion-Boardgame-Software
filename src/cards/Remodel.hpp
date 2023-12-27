#pragma once

#include "../cardTypes/Action.hpp"
#include "../enums.hpp"

// Classe des cartes Rénovation, sous-classe de Action.
class Remodel: public Action {

public:
    Remodel();
    void play(Board &b);
    bool useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand);
};