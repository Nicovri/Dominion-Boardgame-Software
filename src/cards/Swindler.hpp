#pragma once

#include "../cardTypes/Action.hpp"
#include "../cardTypes/Attack.hpp"
#include "../enums.hpp"

// Classe des cartes Escroc, sous-classe de Action et Attaque.
class Swindler: public Action, public Attack {

public:
    Swindler();
    void play(Board &b);
    void attack(Board &b);
    bool useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand);

    bool isActionCard() override { return Action::isActionCard(); }
    bool isAttackCard() override { return Attack::isAttackCard(); }

    bool isVictoryCard() override { return Action::isVictoryCard(); }
    bool isTreasureCard() override { return Action::isTreasureCard(); }
    bool isReactionCard() override { return Action::isReactionCard(); }
};