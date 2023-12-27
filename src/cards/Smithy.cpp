#include "Smithy.hpp"
#include "../game/Board.hpp"

Smithy::Smithy(): Action(4, kEnumToString(KingdomCardName::Smithy), true) {}

/*!
//! Jouer la carte Forgeron: +3 cartes.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Smithy::play(Board &b) {
    b.getCurrentPlayer()->getNewCardsFromDeck(3);
}

bool Smithy::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}