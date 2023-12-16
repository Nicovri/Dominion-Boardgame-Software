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

int Player::getNbCardsInHand() const { return this->hand.size(); }

Card* Player::getCard(int indexInHand) const {
    if(indexInHand <= this->getNbCardsInHand()-1 && indexInHand >= 0) {
        return this->hand.at(indexInHand);
    }
    return NULL;
}

// void Player::assignToGame(Board b) { this->game = &b; }

void Player::setBaseDeck(std::vector<Card*> baseDeck) { this->deck = Pile{baseDeck}; }

void Player::getNewCard(Card *card) {
    this->discard.addCard(card);
    this->nbBuys--;
}

void Player::getDeckFromDiscard() {
    if(this->deck.isEmpty()) {
        this->deck = Pile(this->discard.getCards(discard.getNbCards()));
        discard.clear();
        this->deck.shuffle();
    }
}

void Player::getHandFromDeck() {
    if(hand.empty()) {
        this->hand = this->deck.getCards(5);
    }
    int cardToGet = 5 - hand.size();
    if(hand.size() < 5) {
        this->getDeckFromDiscard();
        this->hand = this->deck.getCards(cardToGet);
    }
}

void Player::getNewCardFromDeck() {
    if(this->deck.isEmpty()) {
        this->getDeckFromDiscard();
    }
    this->hand.push_back(this->deck.getCards(1).at(0));
}

bool Player::hasActionCards() {
    for(Card *c : hand) {
        if(c->isActionCard()) {
            return true;
        }
    }
    return false;
}

bool Player::hasTreasureCards() {
    for(Card *c : hand) {
        if(c->isTreasureCard()) {
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
    Card *c = this->hand.at(indexInHand);
    if(c->isActionCard()) {
        dynamic_cast<Action*>(c)->useEffect();
    }
    if(c->isTreasureCard()) {
        this->nbCoins += dynamic_cast<Treasure*>(c)->getNumberPoints();
    }
}

void Player::finishRound() {
    for(Card *c : this->hand) {
        discard.addCard(c);
    }
    this->hand.clear();
    this->getHandFromDeck();
}

std::ostream& operator<<(std::ostream &os, const Player &p) {
    os << p.username << " : [nbActions=" << p.nbActions << " nbBuys=" << p.nbBuys << " nbCoins=" << p.nbCoins << "]" << std::endl;
    for(int i = 0; i < int(p.hand.size()); i++) {
        os << i << ": " << p.hand.at(i) << std::endl;
    }
    os << std::endl << p.deck << std::endl;
    return os;
}