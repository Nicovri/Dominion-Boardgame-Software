#pragma once

#include "../game/Card.hpp"
#include "../game/Point.hpp"
#include <string>

// Classe des cartes Victoire, sous-classe de Card et de Point.
class Victory: public virtual Card {
    Point points;

public:
    Victory(int price, std::string title, bool isVisible, int points);
    virtual ~Victory() = default;
    int getNumberPoints() const;
    bool isActionCard();
    bool isTreasureCard();
    bool isVictoryCard();
    bool isAttackCard();
    bool isReactionCard();
    virtual void play(Board &b) = 0;

    virtual void setVictoryPoints(Board &b) = 0;
};