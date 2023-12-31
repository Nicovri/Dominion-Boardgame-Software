#include "Player.hpp"
#include "Board.hpp"

Player::Player(std::string username): username(username), nbActions(0), nbBuys(0), nbCoins(0) {}

Player::~Player() {
    // delete &deck;
    // delete &discard;
    // delete &hand;
}

Player::Player(const Player &p): username(p.username), nbActions(p.nbActions), nbBuys(p.nbBuys), nbCoins(p.nbCoins), deck(p.deck), discard(p.discard), hand(p.hand) {}

Player& Player::operator=(const Player& p) {
    if(this != &p) {
        username = p.username;
        nbActions = p.nbActions;
        nbBuys = p.nbBuys;
        nbCoins = p.nbCoins;
        deck = p.deck;
        discard = p.discard;
        hand = p.hand;
    }
    return *this;
}

std::string Player::getUsername() const { return this->username; }

int Player::getNbActions() const { return this->nbActions; }

int Player::getNbBuys() const { return this->nbBuys; }

int Player::getNbCoins() const { return this->nbCoins; }

int Player::getTotalVictoryPoints() const { return this->nbVictory; }

void Player::addVictoryPoints(int nb) { this->nbVictory += nb; }

void Player::addCoins(int nb) { this->nbCoins += nb; }

void Player::addActions(int nb) { this->nbActions += nb; }

void Player::addBuys(int nb) { this->nbBuys += nb; }

int Player::getNbCardsInHand() const { return this->hand.getNbCards(); }

std::string Player::showTitleLastCardInDiscard() const { return !discard.isEmpty() ? discard.showCard(discard.getNbCards()-1)->getTitle() : ""; }

int Player::getNbCardsInDiscard() const { return discard.getNbCards(); }

int Player::getNbCardsInDeck() const { return deck.getNbCards(); }

int Player::getNbCardsTotal() const { return (getNbCardsInHand() + getNbCardsInDeck() + getNbCardsInDiscard()); }

/*!
//! Montre la carte choisie dans la main du joueur. Ne supprime pas la carte de la main.
      \param indexInHand l'index de la carte choisie.
      \return la carte choisie.
*/
Card* Player::showCard(int indexInHand) const {
    if(indexInHand <= this->getNbCardsInHand()-1 && indexInHand >= 0) {
        return this->hand.showCard(indexInHand);
    }
    return NULL;
}

/*!
//! Montre les cartes choisies du deck du joueur. Ne supprime pas ces cartes.
      \param nbCards le nombre de cartes à montrer.
*/
std::vector<Card*> Player::showCardsInDeck(int nbCards) const {
    std::vector<Card*> cards;
    for(int i = 0; i < nbCards; i++) {
        Card *c = deck.showCard(deck.getNbCards() - i - 1);
        if(c != NULL) {
            cards.push_back(c);
        }
    }
    return cards;
}

/*!
//! Montre les cartes choisies de la défausse du joueur. Ne supprime pas ces cartes.
      \param nbCards le nombre de cartes à montrer.
*/
std::vector<Card*> Player::showCardsInDiscard(int nbCards) const {
    std::vector<Card*> cards;
    for(int i = 0; i < nbCards; i++) {
        cards.push_back(discard.showCard(deck.getNbCards() - i - 1));
    }
    return cards;
}

/*!
//! Assigne un joueur à une nouvelle partie.
      \param b le plateau de jeu de la nouvelle partie.
*/
void Player::assignToGame(Board &b) {
    this->game = &b;
    this->deck.assignToGame(*game);
    this->discard.assignToGame(*game);
    this->hand.assignToGame(*game);
}

/*!
//! Donne le deck de base au joueur.
      \param baseDeck le deck de base au début de la partie.
*/
void Player::setBaseDeck(std::vector<Card*> baseDeck) {
    this->deck = Pile{baseDeck};
    this->deck.shuffle();
}

/*!
//! Récupère une nouvelle carte des piles du plateau de jeu et l'ajoute à la défausse.
      \param card la carte récupérée.
      \param isCardEffect la récupération est-elle due à l'effet d'une carte Action?
      \param goesDirectlyInHand la carte récupérée va-t-elle directement dans la main du joueur?
*/
void Player::getNewCard(Card *card, bool isCardEffect, bool goesDirectlyInHand) {
    if(goesDirectlyInHand) {
        this->hand.addCard(card);
    } else {
        this->discard.addCard(card);
    }
    if(!isCardEffect) {
        this->nbBuys--;
        this->nbCoins -= card->getPrice();
    }
}

// Reforme le deck du joueur en mélangeant la défausse lorsque celui-ci est vide.
void Player::getDeckFromDiscard() {
    if(this->deck.isEmpty()) {
        std::vector<Card*> cards = this->discard.getCards(discard.getNbCards());
        this->deck.addCards(cards);
        this->deck.shuffle();
    }
}

// Reforme la main de 5 cartes du joueur à la fin de son tour de jeu.
void Player::getHandFromDeck() {
    if(hand.isEmpty()) {
        this->hand.addCards(this->deck.getCards(5));
    }
    int cardToGet = 5 - hand.getNbCards();
    if(hand.getNbCards() < 5) {
        this->getDeckFromDiscard();
        this->hand.addCards(this->deck.getCards(cardToGet));
    }
}

// Pioche une carte du deck et l'ajoute à la main du joueur.
void Player::getNewCardFromDeck() {
    if(this->deck.isEmpty()) {
        this->getDeckFromDiscard();
    }
    this->hand.addCard(this->deck.getCards(1).at(0));
}

/*!
//! Pioche plusieurs cartes du deck et les ajoute à la main du joueur.
      \param nb le nombre de cartes à piocher.
*/
void Player::getNewCardsFromDeck(int nb) {
    for(int i = 0; i < nb; i++) {
        this->getNewCardFromDeck();
    }
}

/*!
//! Pioche plusieurs cartes du deck et les ajoute à la défausse du joueur.
      \param nbCards le nombre de cartes à piocher.
*/
void Player::addCardsFromDeckToDiscard(int nbCards) {
    std::vector<Card*> cards = deck.getCards(nbCards);
    discard.addCards(cards);
}

/*!
//! Place une carte de la main sur le deck du joueur.
      \param indexInHand l'index de la carte choisie.
      \return false si l'opération n'a pas été effectuée, true si elle l'a été.
*/
bool Player::addCardFromHandToDeck(int indexInHand) {
    if(indexInHand <= this->getNbCardsInHand()-1 && indexInHand >= 0) {
        Card *c = hand.getCard(indexInHand);
        deck.addCard(c);
        return true;
    }
    return false;
}

// Définit le nombre total de points de victoire du joueur.
void Player::setTotalVictoryPoints() {
    this->nbVictory = 0;
    this->discard.setTotalVictoryPoints();
    this->deck.setTotalVictoryPoints();
    this->hand.setTotalVictoryPoints();
}

// Le joueur a-t-il des cartes Action dans sa main ?
bool Player::hasActionCards() {
    for(int i = 0; i < hand.getNbCards(); i++) {
        if(hand.showCard(i)->isActionCard()) {
            return true;
        }
    }
    return false;
}

// Le joueur a-t-il des cartes Trésor dans sa main ?
bool Player::hasTreasureCards() {
    for(int i = 0; i < hand.getNbCards(); i++) {
        if(hand.showCard(i)->isTreasureCard()) {
            return true;
        }
    }
    return false;
}

// Commence le tour d'un joueur en initialisant les différents paramètres.
void Player::beginRound() {
    this->nbActions = 1;
    this->nbBuys = 1;
    this->nbCoins = 0;
    this->setTotalVictoryPoints();
}

/*!
//! Joue une carte de la main du joueur et utilise son effet.
      \param indexInHand l'index de la carte choisie.
      \return false si la carte n'a pas pu être jouée, true si la carte a été jouée.
*/
bool Player::playCard(int indexInHand) {
    Card *c = this->hand.getCard(indexInHand);
    if(c == NULL) { return false; }
    if(c->isActionCard()) {
        this->nbActions--;
    }
    this->discard.addCard(c);
    c->play(*game);
    this->setTotalVictoryPoints();
    return true;
}

bool Player::playActionCard(int indexInHand, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    Card *c = this->hand.getCard(indexInHand);
    if(c == NULL) { return false; }
    if(c->isActionCard()) {
        this->nbActions--;
        bool effectIsOver = dynamic_cast<Action*>(c)->useEffect(*game, repetitiveActionCounter, pileIndex, cardIndexInHand);
        if(effectIsOver) {
            this->discard.addCard(c);
            return true;
        }
    }
    return false;
}

/*!
//! Défausse une carte de la main du joueur.
      \param indexInHand l'index de la carte choisie.
      \return false si la carte n'a pas pu être défaussée, true si la carte a été défaussée.
*/
bool Player::discardCard(int indexInHand) {
    Card *c = this->hand.getCard(indexInHand);
    if(c == NULL) { return false; }
    this->discard.addCard(c);
    return true;
}

/*!
//! Ecarte une carte de la main du joueur.
      \param indexInHand l'index de la carte choisie.
      \return false si la carte n'a pas pu être écartée, true si la carte a été écartée.
*/
bool Player::trashCard(int indexInHand) {
    Card *c = this->hand.getCard(indexInHand);
    if(c == NULL) { return false; }
    return this->game->trashCard(c);
}

/*!
//! Ecarte des cartes de la défausse du joueur.
      \param nbCards le nombre de cartes à écarter.
      \return false si la carte n'a pas pu être écartée, true si la carte a été écartée.
*/
bool Player::trashCardsInDiscard(int nbCards) {
    std::vector<Card*> cards = this->discard.getCards(nbCards);
    for(Card *c : cards) {
        this->game->trashCard(c);
    }
    return true;
}

/*!
//! Ecarte des cartes du deck du joueur.
      \param nbCards le nombre de cartes à écarter.
      \return false si la carte n'a pas pu être écartée, true si la carte a été écartée.
*/
bool Player::trashCardsInDeck(int nbCards) {
    std::vector<Card*> cards = this->deck.getCards(nbCards);
    for(Card *c : cards) {
        this->game->trashCard(c);
    }
    return true;
}

// Termine le tour d'un joueur en reformant sa main initiale de 5 cartes à partir du deck.
void Player::finishRound() {
    std::vector<Card*> cards = this->hand.getCards(hand.getNbCards());
    this->discard.addCards(cards);
    this->getHandFromDeck();
    this->setTotalVictoryPoints();
    this->nbActions = 0;
    this->nbBuys = 0;
    this->nbCoins = 0;
}

bool operator<(const Player& l, const Player& r) {
    return l.getTotalVictoryPoints() < r.getTotalVictoryPoints();
}

std::ostream& operator<<(std::ostream &os, const Player *p) {
    os << p->username << " : [nbActions=" << p->nbActions << " nbBuys=" << p->nbBuys << " nbCoins=" << p->nbCoins << " nbVictory=" << p->nbVictory << "]" << std::endl;
    for(int i = 0; i < int(p->hand.getNbCards()); i++) {
        os << i << ": " << p->hand.showCard(i) << std::endl;
    }
    os << std::endl << "nbCardsInHand: " << p->getNbCardsInHand() << std::endl;
    os << std::endl << "Deck: " << p->deck << std::endl;
    os << std::endl << "Discard: " << p->discard << std::endl;
    return os;
}