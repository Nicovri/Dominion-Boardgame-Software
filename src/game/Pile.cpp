#include "Pile.hpp"

Pile::Pile() {}

Pile::Pile(Card *c, int num) {
    for(int i = 0; i < num; i++) {
        cardStack.push(c);
    }
}

Pile::Pile(std::vector<Card*> cards) {
    for(Card *c : cards) {
        this->cardStack.push(c);
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

//

void Pile::shuffle() {
    srand(time(NULL));
    std::vector<Card*> v = {};
    while(!this->isEmpty()) {
        v.push_back(cardStack.top());
        cardStack.pop();
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(v.begin(), v.end(), g);
    for(auto c : v) {
        cardStack.push(c);
    }
}

bool Pile::isEmpty() const { return cardStack.empty(); }

void Pile::clear() {
    while(!this->isEmpty()) {
        cardStack.pop();
    }
}

int Pile::getNbCards() { return this->cardStack.size(); }

std::vector<Card*> Pile::getCards(int number) {
    std::vector<Card*> cards = {};
    for(int i = 0; i < number; i++) {
        if(!this->isEmpty()) {
            cards.push_back(cardStack.top());
            cardStack.pop();
        }
    }
    return cards;
}

void Pile::addCard(Card *card) {
    this->cardStack.push(card);
}

std::ostream& operator<<(std::ostream &os, const Pile &p) {
    if(!p.isEmpty()) {
        os << p.cardStack.top() << std::endl;
    }
    os << "Cards in the pile: " << p.cardStack.size() << std::endl;
    return os;
}