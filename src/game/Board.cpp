#include "Board.hpp"

Board::Board(std::vector<Player> ps) {
    if(ps.size() < 2 || ps.size() > 4) {
        // Error
    } else  {
        for(auto p : ps) {
            this->players.push_back(p);
        }
    }
}

Board::Board(Player &p1, Player &p2) { this->players.push_back(p1); this->players.push_back(p2); }

Board::Board(Player &p1, Player &p2, Player &p3) { this->players.push_back(p1); this->players.push_back(p2); this->players.push_back(p3); }

Board::Board(Player &p1, Player &p2, Player &p3, Player &p4) { this->players.push_back(p1); this->players.push_back(p2); this->players.push_back(p3); this->players.push_back(p4); }

Board::~Board() {}

int Board::getNbPlayers() const { return this->players.size(); }

int Board::getNbPiles() const { return this->piles.size(); }

Player Board::getCurrentPlayer() const { return this->players.at(currentPlayer); }

int Board::getCurrentPlayerIndex() const { return this->currentPlayer; }

bool Board::initializeBoard(std::vector<Card> baseDeck, std::vector<Pile> piles) {
    for(Player &p : this->players) {
        p.setBaseDeck(baseDeck);
        p.getHandFromDeck();
    }
    for(Pile &p : piles) {
        this->piles.push_back(p);
    }
    this->currentPlayer = 0;
    return true;
}

void Board::playRound() {
    Player *p = &this->players.at(currentPlayer);
    p->beginRound();
    while(p->hasActionCards() || p->getNbActions() > 0) {
        if(!p->hasActionCards()) { break; }
        int cardIndex = -2;
        while(p->getCard(cardIndex).isActionCard() || cardIndex < -1 || cardIndex > p->getNbCardsInHand()-1) {
            std::cout << "Which card would you like to play?: ";
            std::cin >> cardIndex;
        }
        if(cardIndex != -1) {
            p->playCard(cardIndex);
        }
    }
    for(int i = 0; i < p->getNbCardsInHand(); i++) {
        // Never works because the instance is Card and not Treasure as it should be
        if(p->getCard(i).isTreasureCard()) {
            p->playCard(i);
        }
    }
    while(p->getNbBuys() > 0) {
        signed int pileIndex = -2;
        while(pileIndex < -1 || pileIndex > this->getNbPiles()-1) {
            // Error don't have enough coins
            std::cout << "Which card would you like to buy (you currently have " << p->getNbCoins() << " coins)?: ";
            std::cin >> pileIndex;
        }
        if(pileIndex != -1) {
            p->getNewCard(this->piles.at(pileIndex).getCards(1).at(0));
        }
    }
    if(currentPlayer == int(this->players.size())-1) {
        currentPlayer = 0;
    } else {
        currentPlayer++;
    }
    p->finishRound();
}

std::ostream& operator<<(std::ostream &os, const Board &b) {
    os << "============================================================" << std::endl << std::endl;
    for(const Player &p : b.players) {
        os << p << std::endl;
    }
    for(const Pile &p : b.piles) {
        os << p << std::endl;
    }
    os << "============================================================" << std::endl;
    return os;
}