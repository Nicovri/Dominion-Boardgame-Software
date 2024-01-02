#pragma once

#include "../game/Card.hpp"
#include "../cardTypes/Reaction.hpp"
#include "../enums.hpp"
#include <string>

class Board;

// Classe des cartes Attaque, sous-classe de Card.
class Attack: public virtual Card {

public:
    Attack(int price, std::string title, bool isVisible);
    virtual ~Attack() = default;
    bool isActionCard();
    bool isTreasureCard();
    bool isVictoryCard();
    bool isAttackCard();
    bool isReactionCard();
    virtual void play(Board &b) = 0;

    virtual void attack(Board &b) = 0;
    virtual bool useReactionToAttack(Board &b, Player *p);
    virtual bool useCounterAttack(Player *p);
};