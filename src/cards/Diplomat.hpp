#pragma once

#include "../cardTypes/Action.hpp"
#include "../cardTypes/Reaction.hpp"
#include "../game/Player.hpp"
#include "../enums.hpp"

// Classe des cartes Diplomate, sous-classe de Action et Réaction.
class Diplomat: public Action, public Reaction {

public:
    Diplomat();
    void play(Board &b);
    bool react(Board &b, Player *p);
    bool useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand);

    bool isActionCard() override { return Action::isActionCard(); }
    bool isReactionCard() override { return Reaction::isReactionCard(); }

    bool isVictoryCard() override { return Action::isVictoryCard(); }
    bool isTreasureCard() override { return Action::isTreasureCard(); }
    bool isAttackCard() override { return Action::isAttackCard(); }
};