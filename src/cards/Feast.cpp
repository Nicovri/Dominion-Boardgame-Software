#include "Feast.hpp"
#include "../game/Board.hpp"

Feast::Feast(): Action(4, kEnumToString(KingdomCardName::Feast), true) {}

/*!
//! Jouer la carte Festin: écarte cette carte, fait gagner une carte coûtant jusqu'à 5 pièces.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Feast::play(Board &b) {
    Player *p = b.getCurrentPlayer();

    p->trashCardsInDiscard(1);

    int allowedPrice = 5;
    
    Card *c = b.chooseCard(allowedPrice, true);
    if(c != NULL) {
        p->getNewCard(c, true);
    }
}

bool Feast::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}