#pragma once

#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <random>
#include "Card.hpp"

class Board;

// Classe de pile de cartes, tel que le deck, la défausse, le rebut, les piles du plateau et la main du joueur. Une pile doit être assignée à un plateau pour pouvoir l'utiliser correctement.
class Pile {
    std::vector<Card*> cardStack;
    Board *game;

public:
    Pile();
    Pile(Card *c, int num);
    Pile(std::vector<Card*> cards);
    ~Pile();
    Pile(const Pile &p);
    Pile& operator=(const Pile& p);
    
    void assignToGame(Board &b);
    void setTotalVictoryPoints() const;
    void shuffle();
    bool isEmpty() const;
    void clear();
    int getNbCards() const;
    std::vector<Card*> getCards(int number);
    Card* getCard(int cardIndex);
    Card* showCard(int cardIndex) const;
    void addCard(Card *c);
    void addCards(std::vector<Card*> cards);

    friend std::ostream& operator<<(std::ostream &os, const Pile &p);
};