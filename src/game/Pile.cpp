#include "Pile.hpp"

Pile::Pile() {}

Pile::Pile(Card *c, int num) {
    for(int i = 0; i < num; i++) {
        cardStack.push_back(c);
    }
}

Pile::Pile(std::vector<Card*> cards) {
    for(Card *c : cards) {
        this->cardStack.push_back(c);
    }
}

Pile::~Pile() {}

Pile::Pile(const Pile &p): cardStack(p.cardStack) {}

Pile& Pile::operator=(const Pile &p) {
    if(this != &p) {
        cardStack = p.cardStack;
    }
    return *this;
}

void Pile::assignToGame(Board &b) { this->game = &b; }

void Pile::setTotalVictoryPoints() const {
    for(const auto& card : cardStack) {
        if(card->isVictoryCard()) {
            card->play(*game);
        }
    }
}

void Pile::shuffle() {
    if(!this->isEmpty()) {
        srand(time(NULL));
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cardStack.begin(), cardStack.end(), g);
    }
}

bool Pile::isEmpty() const { return cardStack.empty(); }

void Pile::clear() {
    while(!this->isEmpty()) {
        cardStack.pop_back();
    }
}

int Pile::getNbCards() const { return this->cardStack.size(); }

std::vector<Card*> Pile::getCards(int number) {
    std::vector<Card*> cards = {};
    for(int i = 0; i < number; i++) {
        if(!this->isEmpty()) {
            cards.push_back(cardStack.at(cardStack.size()-1));
            cardStack.pop_back();
        }
    }
    return cards;
}

Card* Pile::getCard(int cardIndex) const {
    Card *c = this->cardStack.at(cardIndex);
    return c;
}

void Pile::addCard(Card *card) {
    this->cardStack.push_back(card);
}

void Pile::addCards(std::vector<Card*> cards) {
    for(Card *card: cards) {
        this->cardStack.push_back(card);
    }
}

std::ostream& operator<<(std::ostream &os, const Pile &p) {
    if(!p.isEmpty()) {
        os << p.cardStack.at(p.cardStack.size()-1) << std::endl;
    }
    os << "Cards in the pile: " << p.cardStack.size() << std::endl;
    return os;
}