#include "Laboratory.hpp"
#include "../game/Board.hpp"

Laboratory::Laboratory(): Card(5, kEnumToString(KingdomCardName::Laboratory), true),
                            Action(5, kEnumToString(KingdomCardName::Laboratory), true) {}

/*!
//! Jouer la carte Laboratoire: +2 cartes, +1 action.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Laboratory::play(Board &b) {
    b.getCurrentPlayer()->getNewCardsFromDeck(2);
    b.getCurrentPlayer()->addActions(1);
}

bool Laboratory::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}