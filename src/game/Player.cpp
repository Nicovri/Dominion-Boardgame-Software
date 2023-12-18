#include "Player.hpp"

Player::Player(std::string username): username(username), nbActions(0), nbBuys(0), nbCoins(0) {}

Player::~Player() {}

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

void Player::getNewCard(Card *card, bool isCardEffect) {
    this->discard.addCard(card);
    if(!isCardEffect) {
        this->nbBuys--;
    }
}

void Player::getDeckFromDiscard() {
    if(this->deck.isEmpty()) {
        this->deck.addCards(this->discard.getCards(discard.getNbCards()));
        discard.clear();
        this->deck.shuffle();
    }
}

void Player::getHandFromDeck() {
    if(hand.isEmpty()) {
        this->hand = this->deck.getCards(5);
    }
    int cardToGet = 5 - hand.getNbCards();
    if(hand.getNbCards() < 5) {
        this->getDeckFromDiscard();
        this->hand = this->deck.getCards(cardToGet);
    }
}

void Player::getNewCardFromDeck() {
    if(this->deck.isEmpty()) {
        this->getDeckFromDiscard();
    }
    this->hand.addCard(this->deck.getCards(1).at(0));
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
}

void Player::playCard(int indexInHand) {
    Card *c = this->hand.getCard(indexInHand);
    if(c->isActionCard()) {
        this->nbActions--;
        dynamic_cast<Action*>(c)->useEffect(*game);
    }
    if(c->isTreasureCard()) {
        c->play(*game);
    }
}

void Player::finishRound() {
    this->discard.addCards(this->hand.getCards(hand.getNbCards()));
    this->hand.clear();
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
    os << std::endl << "Deck: " << p->deck << std::endl;
    return os;
}