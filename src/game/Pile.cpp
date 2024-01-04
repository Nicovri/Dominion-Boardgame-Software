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

Pile::~Pile() {
    // for(Card *c : cardStack) {
    //     if(c != NULL) {
    //         delete &c;
    //     }
    // }
}

Pile::Pile(const Pile &p): cardStack(p.cardStack) {}

Pile& Pile::operator=(const Pile &p) {
    if(this != &p) {
        cardStack = p.cardStack;
    }
    return *this;
}

/*!
//! Assigne une pile à une nouvelle partie.
      \param b le plateau de jeu de la nouvelle partie.
*/
void Pile::assignToGame(Board &b) { this->game = &b; }

// Définit le nombre total de points de victoire d'une pile.
void Pile::setTotalVictoryPoints() const {
    if(!this->isEmpty()) {
        for(const auto& card : cardStack) {
            if(card->isVictoryCard()) {
                dynamic_cast<Victory*>(card)->setVictoryPoints(*game);
            }
        }
    }
}

// Mélange une pile aléatoirement.
void Pile::shuffle() {
    if(!this->isEmpty()) {
        srand(time(NULL));
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cardStack.begin(), cardStack.end(), g);
    }
}

// La pile est-elle vide?
bool Pile::isEmpty() const { return cardStack.empty(); }

// Vide la pile de toute carte qu'elle contient.
void Pile::clear() {
    while(!this->isEmpty()) {
        cardStack.pop_back();
    }
}

// Donne le nombre de cartes contenues dans une pile.
int Pile::getNbCards() const { return this->cardStack.size(); }

/*!
//! Pioche pusieurs cartes d'une pile. Le nombre de cartes retourné peut être plus petit si jamais la pile se vide avant.
    \param number le nombre de cartes à récupérer.
    \return les cartes piochées dans la pile.
*/
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

/*!
//! Pioche une carte spécifique d'une pile, si cela est possible.
    \param cardIndex l'index de la carte à piocher dans la pile.
    \return la carte piochée dans la pile.
*/
Card* Pile::getCard(int cardIndex) {
    if(0 <= cardIndex && cardIndex <= int(cardStack.size())-1) {
        Card *c = this->cardStack.at(cardIndex);
        this->cardStack.erase(cardStack.begin() + cardIndex);
        return c;
    } else {
        return NULL;
    }
}

/*!
//! Montre une carte d'une pile. Cette méthode ne supprime pas la carte de la pile.
    \param cardIndex l'index de la carte à regarder dans la pile.
    \return la carte à regarder dans la pile.
*/
Card* Pile::showCard(int cardIndex) const {
    if(0 <= cardIndex && cardIndex <= int(cardStack.size())-1) {
        Card *c = this->cardStack.at(cardIndex);
        return c;
    } else {
        return NULL;
    }
}

/*!
//! Ajoute une carte à une pile.
    \param card la carte à ajouter.
*/
void Pile::addCard(Card *card) {
    this->cardStack.push_back(card);
}

/*!
//! Ajoute plusieurs cartes à une pile.
    \param cards la liste des cartes à ajouter.
*/
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