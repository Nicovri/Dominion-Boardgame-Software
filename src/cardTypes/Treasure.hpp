#pragma once

#include "../game/Card.hpp"
#include "../game/Point.hpp"
#include <string>

class Treasure: public Card, public Point {

public:
    Treasure(int price, std::string title, bool isVisible, int points);
    virtual ~Treasure() = default;
    bool isActionCard();
    bool isTreasureCard();
    bool isVictoryCard();
};