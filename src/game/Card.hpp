#pragma once

#include <string>
#include <iostream>

class Card {
    int price;
    std::string title;
    bool isVisible;

public:
    Card();
    Card(int price, std::string title, bool isVisible);
    virtual ~Card() = default;
    virtual bool isActionCard();
    virtual bool isTreasureCard();
    virtual bool isVictoryCard();
    // virtual void playCard() = 0;

    friend std::ostream& operator<<(std::ostream &os, const Card &c);
};