#pragma once

#include "Pile.hpp"
// #include "Board.hpp"
#include "Card.hpp"
#include "../cardTypes/Action.hpp"
#include "../cardTypes/Treasure.hpp"
#include <string>
#include <iostream>
#include <vector>

class Board;

// Classe de joueur. Contient toutes les actions possibles qu'un joueur peut effectuer durant la partie. Un joueur doit être assigné à un plateau pour pouvoir jouer correctement.
class Player {
    std::string username;
    int nbActions;
    int nbBuys;
    int nbCoins;
    int nbVictory;
    Pile deck;
    Pile discard;
    Pile hand;
    Board *game;

public:
    Player(std::string username);
    ~Player();
    Player(const Player &p);
    Player& operator=(const Player& p);
    std::string getUsername() const;
    int getNbActions() const;
    int getNbBuys() const;
    int getNbCoins() const;
    int getTotalVictoryPoints() const;

    void addVictoryPoints(int nb);
    void addCoins(int nb);
    void addActions(int nb);
    void addBuys(int nb);
    int getNbCardsInHand() const;
    Card* showCard(int indexInHand) const;
    void assignToGame(Board &b);
    void setBaseDeck(std::vector<Card*> baseDeck);
    void getNewCard(Card *card, bool isCardEffect, bool goesDirectlyInHand=false);
    void getDeckFromDiscard();
    void getHandFromDeck();
    void getNewCardFromDeck();
    void getNewCardsFromDeck(int nb);
    void setTotalVictoryPoints();
    bool hasActionCards();
    bool hasTreasureCards();
    void beginRound();
    bool playCard(int indexInHand);
    bool discardCard(int indexInHand);
    bool trashCard(int indexInHand);
    void finishRound();

    friend bool operator<(const Player& l, const Player& r);
    friend std::ostream& operator<<(std::ostream &os, const Player *p);

    bool playActionCard(int indexInHand, int repetitiveActionCounter, int pileIndex, int cardIndexInHand);
    std::string showTitleLastCardInDiscard() const;
    int getNbCardsInDiscard() const;
    int getNbCardsInDeck() const;
    int getNbCardsTotal() const;
    bool trashCardsInDiscard(int nbCards);
    bool trashCardsInDeck(int nbCards);
    std::vector<Card*> showCardsInDeck(int nbCards) const;
    std::vector<Card*> showCardsInDiscard(int nbCards) const;
    void addCardsFromDeckToDiscard(int nbCards);
    bool addCardFromHandToDeck(int indexInHand);
    bool addCardFromDiscardToDeck(int indexInDiscard);
};