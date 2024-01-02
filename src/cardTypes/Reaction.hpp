#pragma once

#include "../game/Card.hpp"
#include "../game/Player.hpp"
#include <string>

// Classe des cartes Réaction, sous-classe de Card.
class Reaction: public virtual Card {
    /*
        0: When another player plays an Attack card.
        1: When you gain a card.
        etc.
    */
    int conditionTriggered;

public:
    Reaction(int price, std::string title, bool isVisible, int conditionTriggered);
    virtual ~Reaction() = default;
    int getConditionTriggered() const;
    bool isActionCard();
    bool isTreasureCard();
    bool isVictoryCard();
    bool isAttackCard();
    bool isReactionCard();
    virtual void play(Board &b) = 0;

    // Jouer l'effet de la carte si le joueur la révèle selon la condition indiquée.
    virtual bool react(Board &b, Player *p) = 0;
};