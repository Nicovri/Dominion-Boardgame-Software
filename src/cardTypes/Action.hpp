#pragma once

#include "../game/Card.hpp"
#include <string>

class Action: public Card {
    std::string effectText;

public:
    Action(int price, std::string title, bool isVisible);
    Action(int price, std::string title, bool isVisible, std::string effectText);
    virtual ~Action() = default;
    std::string getEffectText() const;
    bool isActionCard();
    bool isTreasureCard();
    bool isVictoryCard();
    virtual void play(Board &b) = 0;
    virtual bool useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) = 0;
};