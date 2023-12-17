#include "Board.hpp"

Board::Board(std::vector<Player*> ps) {
    if(ps.size() < 2 || ps.size() > 4) {
        // Error
    } else  {
        for(auto p : ps) {
            this->players.push_back(p);
        }
    }
}

Board::Board(Player &p1, Player &p2) { this->players.push_back(&p1); this->players.push_back(&p2); }

Board::Board(Player &p1, Player &p2, Player &p3) { this->players.push_back(&p1); this->players.push_back(&p2); this->players.push_back(&p3); }

Board::Board(Player &p1, Player &p2, Player &p3, Player &p4) { this->players.push_back(&p1); this->players.push_back(&p2); this->players.push_back(&p3); this->players.push_back(&p4); }

Board::~Board() {}

int Board::getNbPlayers() const { return this->players.size(); }

int Board::getNbPiles() const { return this->piles.size(); }

Player* Board::getCurrentPlayer() const { return this->players.at(currentPlayer); }

int Board::getCurrentPlayerIndex() const { return this->currentPlayer; }

bool Board::initializeBoard(std::vector<Card*> baseDeck, std::vector<Pile> piles) {
    for(const auto &p : this->players) {
        p->assignToGame(*this);
        p->setBaseDeck(baseDeck);
        p->getHandFromDeck();
    }
    for(Pile &p : piles) {
        p.assignToGame(*this);
        trash.assignToGame(*this);
        this->piles.push_back(p);
    }
    this->currentPlayer = 0;
    this->provincePileIndex = -1;
    for(int i = 0; i < int(this->piles.size()); i++) {
        if(!this->piles.at(i).isEmpty() && this->piles.at(i).getCard(0)->isVictoryCard() && dynamic_cast<Victory*>(this->piles.at(i).getCard(0))->getNumberPoints() == 6) {
            provincePileIndex = i;
            break;
        }
    }
    std::cout << provincePileIndex << std::endl;
    return true;
}

void Board::playRound() {
    Player *p = this->players.at(currentPlayer);
    p->beginRound();
    while(p->hasActionCards() || p->getNbActions() > 0) {
        if(!p->hasActionCards()) { break; }
        int cardIndex = -2;
        while(p->getCard(cardIndex)->isActionCard() || cardIndex < -1 || cardIndex > p->getNbCardsInHand()-1) {
            std::cout << "Which card would you like to play?: ";
            std::cin >> cardIndex;

            if(std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cardIndex = -2;
            }
        }
        if(cardIndex != -1) {
            p->playCard(cardIndex);
        }
    }

    for(int i = 0; i < p->getNbCardsInHand(); i++) {
        if(p->getCard(i)->isTreasureCard()) {
            p->playCard(i);
        }
    }
    
    while(p->getNbBuys() > 0) {
        int pileIndex = -2;
        while(pileIndex < -1 || pileIndex > this->getNbPiles()-1 ||
            (0 <= pileIndex  && pileIndex <= this->getNbPiles()-1 && piles.at(pileIndex).getCard(0)->getPrice() > p->getNbCoins())) {
            std::cout << "Which card would you like to buy (you currently have " << p->getNbCoins() << " coins)?: ";
            std::cin >> pileIndex;

            if(std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                pileIndex = -2;
            }
        }
        if(pileIndex != -1) {
            p->getNewCard(this->piles.at(pileIndex).getCards(1).at(0));
        }
    }
    p->finishRound();
    if(currentPlayer == int(this->players.size())-1) {
        currentPlayer = 0;
    } else {
        currentPlayer++;
    }
}

void Board::showResults() {
    std::sort(players.rbegin(), players.rend());
    std::cout << "Game is over! Here are the results." << std::endl;
    for(int i = 1; i <= int(players.size()); i++) {
        std::cout << i << ": " << players.at(i-1)->getUsername() << " with " << players.at(i-1)->getTotalVictoryPoints() << " VP" << std::endl;
    }
    std::cout << "Well done!" << std::endl;
}

bool Board::gameIsOver() {
    if(provincePileIndex != -1 && this->piles.at(provincePileIndex).isEmpty()) {
        return true;
    }

    int emptyPiles = 0;
    for(int i = 0; i < int(this->piles.size()); i++) {
        if(i != provincePileIndex && piles.at(i).isEmpty()) {
            emptyPiles++;
        }
    }
    return emptyPiles >= 3;
}

std::ostream& operator<<(std::ostream &os, const Board &b) {
    os << "============================================================" << std::endl << std::endl;
    for(const auto &p : b.players) {
        os << p << std::endl;
    }
    for(const Pile &p : b.piles) {
        os << p << std::endl;
    }
    os << "============================================================" << std::endl;
    return os;
}