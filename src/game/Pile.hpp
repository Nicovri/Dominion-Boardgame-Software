#pragma once

#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <random>
#include "Card.hpp"

class Pile {
    std::stack<Card> cardStack;

public:
    Pile();
    Pile(Card c, int num);
    Pile(std::vector<Card> cards);
    ~Pile();
    Pile(const Pile &p);
    Pile& operator=(const Pile& p);
    int getTotalVictoryPoints() const;
    void shuffle();
    bool isEmpty() const;
    void clear();
    int getNbCards();
    std::vector<Card> getCards(int number); // Error check if enough cards
    void addCard(Card c);

    friend std::ostream& operator<<(std::ostream &os, const Pile &p);
};