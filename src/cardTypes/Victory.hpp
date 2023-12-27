#pragma once

#include "../game/Card.hpp"
#include "../game/Point.hpp"
#include <string>

// Classe des cartes Victoire, sous-classe de Card et de Point.
class Victory: public Card, public Point {

public:
    Victory(int price, std::string title, bool isVisible, int points);
    virtual ~Victory() = default;
    bool isActionCard();
    bool isTreasureCard();
    bool isVictoryCard();
    virtual void play(Board &b) = 0;
};