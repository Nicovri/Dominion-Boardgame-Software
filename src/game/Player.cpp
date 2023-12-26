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

Card* Player::showCard(int indexInHand) const {
    if(indexInHand <= this->getNbCardsInHand()-1 && indexInHand >= 0) {
        return this->hand.showCard(indexInHand);
    }
    return NULL;
}

void Player::assignToGame(Board &b) {
    this->game = &b;
    this->deck.assignToGame(*game);
    this->discard.assignToGame(*game);
    this->hand.assignToGame(*game);
}

void Player::setBaseDeck(std::vector<Card*> baseDeck) {
    this->deck = Pile{baseDeck};
    this->deck.shuffle();
}

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

void Player::getDeckFromDiscard() {
    if(this->deck.isEmpty()) {
        std::vector<Card*> cards = this->discard.getCards(discard.getNbCards());
        this->deck.addCards(cards);
        this->deck.shuffle();
    }
}

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

void Player::getNewCardFromDeck() {
    if(this->deck.isEmpty()) {
        this->getDeckFromDiscard();
    }
    this->hand.addCard(this->deck.getCards(1).at(0));
}

void Player::getNewCardsFromDeck(int nb) {
    for(int i = 0; i < nb; i++) {
        this->getNewCardFromDeck();
    }
}

void Player::setTotalVictoryPoints() {
    this->nbVictory = 0;
    this->discard.setTotalVictoryPoints();
    this->deck.setTotalVictoryPoints();
    this->hand.setTotalVictoryPoints();
}

bool Player::hasActionCards() {
    for(int i = 0; i < hand.getNbCards(); i++) {
        if(hand.showCard(i)->isActionCard()) {
            return true;
        }
    }
    return false;
}

bool Player::hasTreasureCards() {
    for(int i = 0; i < hand.getNbCards(); i++) {
        if(hand.showCard(i)->isTreasureCard()) {
            return true;
        }
    }
    return false;
}

void Player::beginRound() {
    this->nbActions = 1;
    this->nbBuys = 1;
    this->nbCoins = 0;
}

bool Player::playCard(int indexInHand) {
    Card *c = this->hand.getCard(indexInHand);
    if(c == NULL) { return false; }
    if(c->isActionCard()) {
        this->nbActions--;
    }
    c->play(*game);
    this->discard.addCard(c);
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

bool Player::discardCard(int indexInHand) {
    Card *c = this->hand.getCard(indexInHand);
    if(c == NULL) { return false; }
    this->discard.addCard(c);
    return true;
}

bool Player::trashCard(int indexInHand) {
    Card *c = this->hand.getCard(indexInHand);
    if(c == NULL) { return false; }
    return this->game->trashCard(c);
}

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