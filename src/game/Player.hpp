#pragma once

#include "Pile.hpp"
// #include "Board.hpp"
#include "Card.hpp"
#include "../cardTypes/Action.hpp"
#include "../cardTypes/Treasure.hpp"
#include <string>
#include <iostream>
#include <vector>

class Player {
    std::string username;
    int nbActions;
    int nbBuys;
    int nbCoins;
    Pile deck;
    Pile discard;
    std::vector<Card*> hand;
    // Board *game;

public:
    Player(std::string username);
    ~Player();
    Player(const Player &p);
    Player& operator=(const Player& p);
    std::string getUsername() const;
    int getNbActions() const;
    int getNbBuys() const;
    int getNbCoins() const;
    int getNbCardsInHand() const;
    Card* getCard(int indexInHand) const;

    // void assignToGame(Board b);
    void setBaseDeck(std::vector<Card*> baseDeck);
    void getNewCard(Card *card);
    void getDeckFromDiscard();
    void getHandFromDeck();
    void getNewCardFromDeck();
    int getTotalVictoryPoints() const;
    bool hasActionCards();
    bool hasTreasureCards();
    void beginRound();
    void playCard(int indexInHand);
    void finishRound();

    friend std::ostream& operator<<(std::ostream &os, const Player &p);
};