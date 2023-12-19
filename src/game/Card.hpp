#pragma once

#include <string>
#include <iostream>

class Board;
class Card {
    int price;
    std::string title;
    bool isVisible;

public:
    Card();
    Card(int price, std::string title, bool isVisible);
    virtual ~Card() = default;
    virtual int getPrice() const;
    virtual std::string getTitle() const;
    virtual bool isActionCard() = 0;
    virtual bool isTreasureCard() = 0;
    virtual bool isVictoryCard() = 0;
    virtual void play(Board &b) = 0;

    friend std::ostream& operator<<(std::ostream &os, const Card *c);
};