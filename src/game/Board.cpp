#include "Board.hpp"

Board::Board() {}

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

Board::~Board() {
    // for(Pile p : piles) {
    //     delete &p;
    // }
    // delete &trash;
    // for(Player *p : players) {
    //     delete &p;
    // }
}

int Board::getCurrentPlayerIndex() const { return this->currentPlayer; }

std::vector<Player*> Board::getPlayers() const { return this->players; }

std::vector<Pile> Board::getPiles() const { return this->piles; }

int Board::getNbPlayers() const { return this->players.size(); }

int Board::getNbPiles() const { return this->piles.size(); }

Player* Board::getCurrentPlayer() const { return this->players.at(currentPlayer); }

std::string Board::showTitleLastCardInTrash() const { return !trash.isEmpty() ? trash.showCard(trash.getNbCards()-1)->getTitle() : ""; }

int Board::getNbCardsInTrash() const { return trash.getNbCards(); }

int Board::getNbEmptyPiles() const {
    int nb = 0;
    for(Pile p : piles) {
        if(p.isEmpty()) {
            nb++;
        }
    }
    return nb;
}

/*!
//! Initialise le plateau de jeu. Assigne des joueurs, des piles et récupère l'index de la pile des cartes Province pour l'observation de la fin de partie.
    \param baseDeck le deck de base des joueurs au début de la partie.
    \param piles les piles utilisées sur le plateau de jeu.
    \return false si l'initialisation s'est mal passée, true si elle s'est bien passée.
*/
bool Board::initializeBoard(std::vector<Card*> baseDeck, std::vector<Pile> piles) {
    this->currentPlayer = 0;
    for(const auto &p : this->players) {
        p->assignToGame(*this);
        p->setBaseDeck(baseDeck);
        p->getHandFromDeck();
        p->setTotalVictoryPoints();
        this->currentPlayer++;
    }
    for(Pile &p : piles) {
        p.assignToGame(*this);
        trash.assignToGame(*this);
        this->piles.push_back(p);
    }
    this->currentPlayer = 0;
    this->provincePileIndex = -1;
    for(int i = 0; i < int(this->piles.size()); i++) {
        if(!this->piles.at(i).isEmpty() && this->piles.at(i).showCard(0)->isVictoryCard() && dynamic_cast<Victory*>(this->piles.at(i).showCard(0))->getNumberPoints() == 6) {
            provincePileIndex = i;
            break;
        }
    }
    return true;
}

/*!
//! Laisse l'utilisateur choisir une carte d'une pile du plateau ayant un certain prix.
    \param allowedPrice le prix maximum autorisé de la carte.
    \param isCardEffect la carte est-elle choisie suite à l'effet d'une carte?
    \return la carte choisie par le joueur.
*/
Card* Board::chooseCard(int allowedPrice, bool isCardEffect) {
    int pileIndex = -2;
    Player *p = this->players.at(currentPlayer);

    displayFilteredPiles([allowedPrice](const Pile p) { return !p.isEmpty() && p.showCard(0)->getPrice() <= allowedPrice; });

    while(pileIndex < -1 || pileIndex > this->getNbPiles()-1 ||
        (0 <= pileIndex  && pileIndex <= this->getNbPiles()-1 && (piles.at(pileIndex).isEmpty() || piles.at(pileIndex).showCard(0)->getPrice() > allowedPrice))) {
        std::cout << p << std::endl;
        if(isCardEffect) {
            std::cout << p->getUsername() << ", which card would you like to choose (the maximum allowed price is " << allowedPrice << " coins)?: ";
        } else {
            std::cout << p->getUsername() << ", which card would you like to buy (you currently have " << allowedPrice << " coins)?: ";
        }
        std::cin >> pileIndex;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            pileIndex = -2;
        }
    }
    if(pileIndex != -1) {
        return piles.at(pileIndex).getCards(1).at(0);
    }
    return NULL;
}

/*!
//! Choisit une carte d'une pile du plateau ayant un certain prix.
    \param allowedPrice le prix maximum autorisé de la carte.
    \param pileIndex l'index de la pile choisie.
    \return la carte choisie.
*/
Card* Board::chooseCard(int allowedPrice, int pileIndex) {
    if(pileIndex >= 0 && pileIndex <= getNbPiles()-1 && !piles.at(pileIndex).isEmpty() && piles.at(pileIndex).showCard(0)->getPrice() <= allowedPrice) {
        return piles.at(pileIndex).getCards(1).at(0);
    }
    return NULL;
}

/*!
//! Choisit une carte d'une pile du plateau selon le nom.
    \param cardName le nom de la carte choisie.
    \return la carte choisie.
*/
Card* Board::chooseCard(std::string cardName) {
    Card *c = NULL;
    for(Pile p : this->piles) {
        if(!p.isEmpty() && p.showCard(0)->getTitle() == cardName) {
            c = p.getCards(1).at(0);
        }
    }
    return c;
}

/*!
//! Ajoute une carte au rebut.
    \param c la carte écartée.
    \return false si l'opération n'a pas été effectuée, true si cela s'est bien passé.
*/
bool Board::trashCard(Card *c) {
    this->trash.addCard(c);
    return true;
}

// Joue la carte action demandée par le joueur courant.
void Board::playActionCard() {
    Player *p = this->players.at(currentPlayer);
    while(p->hasActionCards() && p->getNbActions() > 0) {
        int cardIndex = -2;
        while((0 <= cardIndex && cardIndex <= p->getNbCardsInHand()-1 && !p->showCard(cardIndex)->isActionCard()) ||
                cardIndex < -1 || cardIndex > p->getNbCardsInHand()-1) {
            std::cout << p << std::endl;
            std::cout << p->getUsername() << ", which card would you like to play?: ";
            std::cin >> cardIndex;

            if(std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cardIndex = -2;
            }
        }
        if(cardIndex != -1) {
            p->playCard(cardIndex);
        } else {
            break;
        }
    }
}

// Passe au tour du joueur suivant.
void Board::nextPlayerRound() {
    if(currentPlayer == int(this->players.size())-1) {
        currentPlayer = 0;
    } else {
        currentPlayer++;
    }
}

// Joue le tour du joueur courant.
void Board::playRound() {
    Player *p = this->players.at(currentPlayer);
    p->beginRound();

    this->playActionCard();

    std::vector<int> treasuresInHand = {};
    for(int i = p->getNbCardsInHand()-1; i >= 0; i--) {
        if(p->showCard(i)->isTreasureCard()) {
            treasuresInHand.push_back(i);
        }
    }
    for(int i : treasuresInHand) {
        std::cout << "Played " << p->showCard(i) << std::endl;
        p->playCard(i);
    }
    std::cout << std::endl;
    
    while(p->getNbBuys() > 0) {
        Card *c = this->chooseCard(p->getNbCoins(), false);
        if(c != NULL) {
            p->getNewCard(c, false);
        } else {
            break;
        }
    }

    p->finishRound();
    
    this->nextPlayerRound();
}

// Affiche les résultats de fin de partie.
void Board::showResults() {
    std::sort(players.rbegin(), players.rend(), [](const Player* l, const Player* r) {
        return l->getTotalVictoryPoints() < r->getTotalVictoryPoints();
    });
    std::cout << "Game is over! Here are the results." << std::endl;
    for(int i = 1; i <= int(players.size()); i++) {
        std::cout << i << ": " << players.at(i-1)->getUsername() << " with " << players.at(i-1)->getTotalVictoryPoints() << " VP" << std::endl;
    }
    std::cout << "Well done!" << std::endl;
}

// Vérifie si la condition de fin de jeu est complétée.
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

void Board::displayFilteredPiles(std::function<bool(const Pile)> predicate) {
    std::cout << "============================================================" << std::endl << std::endl;
    int i = 0;
    for(const Pile &p : this->piles) {
        if(predicate(p)) {
            std::cout << i << ": " << p << std::endl;
        }
        i++;
    }
    std::cout << "============================================================" << std::endl << std::endl;
}

std::ostream& operator<<(std::ostream &os, const Board &b) {
    os << "============================================================" << std::endl << std::endl;
    // for(const auto &p : b.players) {
    //     os << p << std::endl;
    // }
    int i = 0;
    for(const Pile &p : b.piles) {
        os << i << ": " << p << std::endl;
        i++;
    }
    os << "Trash: " << b.trash << std::endl;
    os << "============================================================" << std::endl;
    return os;
}