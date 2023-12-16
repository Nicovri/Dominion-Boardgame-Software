#include "Player.hpp"
#include "Card.hpp"
#include <vector>
#include <iostream>

class Board {
    std::vector<Player> players;
    int currentPlayer;
    std::vector<Pile> piles;
    Pile trash;

public:
    Board(std::vector<Player> ps);
    Board(Player &p1, Player &p2);
    Board(Player &p1, Player &p2, Player &p3);
    Board(Player &p1, Player &p2, Player &p3, Player &p4);
    ~Board();
    int getNbPlayers() const;
    int getNbPiles() const;
    Player getCurrentPlayer() const;
    int getCurrentPlayerIndex() const;
    bool initializeBoard(std::vector<Card*> baseDeck, std::vector<Pile> piles);
    void playRound();

    friend std::ostream& operator<<(std::ostream &os, const Board &b);
};