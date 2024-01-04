#pragma once

#include "../cardTypes/Action.hpp"
#include "../cardTypes/Victory.hpp"
#include "../enums.hpp"

// Classe des cartes Moulin, sous-classe de Action et Victory.
class Mill: public Action, public Victory {

public:
    Mill();
    void play(Board &b);
    void setVictoryPoints(Board &b);
    bool useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand);

    bool isActionCard() override { return Action::isActionCard(); }
    bool isVictoryCard() override { return Victory::isVictoryCard(); }

    bool isTreasureCard() override { return Action::isTreasureCard(); }
    bool isAttackCard() override { return Action::isAttackCard(); }
    bool isReactionCard() override { return Action::isReactionCard(); }
};