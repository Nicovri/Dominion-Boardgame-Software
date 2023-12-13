#pragma once

#include "../game/Card.hpp"
#include "../game/Point.hpp"
#include <string>

class Victory: public Card, public Point {

public:
    Victory(int price, std::string title, bool isVisible, int points);
    virtual ~Victory() = default;
    bool isActionCard();
    bool isTreasureCard();
    bool isVictoryCard();
};