#include "Player.hpp"
#include "Card.hpp"
#include "../cardTypes/Victory.hpp"
#include <vector>
#include <iostream>
#include <functional>

class Board {
    std::vector<Player*> players;
    int currentPlayer;
    std::vector<Pile> piles;
    int provincePileIndex;
    Pile trash;

public:
    Board(std::vector<Player*> ps);
    Board(Player &p1, Player &p2);
    Board(Player &p1, Player &p2, Player &p3);
    Board(Player &p1, Player &p2, Player &p3, Player &p4);
    ~Board();
    int getCurrentPlayerIndex() const;
    std::vector<Player*> getPlayers() const;

    int getNbPlayers() const;
    int getNbPiles() const;
    Player* getCurrentPlayer() const;
    bool initializeBoard(std::vector<Card*> baseDeck, std::vector<Pile> piles);
    Card* chooseCard(int allowedPrice, bool isCardEffect);
    Card* chooseCard(std::string cardName);
    bool trashCard(Card* c);
    void playActionCard();
    void playRound();
    void showResults();
    bool gameIsOver();
    void displayFilteredPiles(std::function<bool(const Pile)> predicate);

    friend std::ostream& operator<<(std::ostream &os, const Board &b);
};