#pragma once

#include "../game/Card.hpp"
#include "../game/Point.hpp"
#include <string>

// Classe des cartes Trésor, sous-classe de Card et de Point.
class Treasure: public virtual Card {
    Point points;

public:
    Treasure(int price, std::string title, bool isVisible, int points);
    virtual ~Treasure() = default;
    int getNumberPoints() const;
    bool isActionCard();
    bool isTreasureCard();
    bool isVictoryCard();
    bool isAttackCard();
    bool isReactionCard();
    virtual void play(Board &b) = 0;
};