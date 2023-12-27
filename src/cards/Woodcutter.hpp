#pragma once

#include "../cardTypes/Action.hpp"
#include "../enums.hpp"

// Classe des cartes Bûcheron, sous-classe de Action.
class Woodcutter: public Action {

public:
    Woodcutter();
    void play(Board &b);
    bool useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand);
};