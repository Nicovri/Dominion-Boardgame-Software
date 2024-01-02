#pragma once

#include "../cardTypes/Action.hpp"
#include "../cardTypes/Reaction.hpp"
#include "../game/Player.hpp"
#include "../enums.hpp"

// Classe des cartes Douves, sous-classe de Action et Réaction.
class Moat: public Action, public Reaction {

public:
    Moat();
    void play(Board &b);
    bool react(Board &b, Player *p);
    bool useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand);

    bool isActionCard() override { return Action::isActionCard(); }
    bool isReactionCard() override { return Reaction::isReactionCard(); }

    bool isVictoryCard() override { return Action::isVictoryCard(); }
    bool isTreasureCard() override { return Action::isTreasureCard(); }
    bool isAttackCard() override { return Action::isAttackCard(); }
};