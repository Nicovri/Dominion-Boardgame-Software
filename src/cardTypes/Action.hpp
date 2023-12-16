#pragma once

#include "../game/Card.hpp"

class Action: public Card {

public:
    Action(int price, std::string title, bool isVisible);
    virtual ~Action() = default;
    bool isActionCard();
    bool isTreasureCard();
    bool isVictoryCard();
    virtual void play() = 0;
    virtual void useEffect();
};