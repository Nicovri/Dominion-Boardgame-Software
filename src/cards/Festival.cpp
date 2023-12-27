#include "Festival.hpp"
#include "../game/Board.hpp"

Festival::Festival(): Action(5, kEnumToString(KingdomCardName::Festival), true) {}

/*!
//! Jouer la carte Festival: +2 actions, +1 achat, +2 pièces.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Festival::play(Board &b) {
    b.getCurrentPlayer()->addActions(2);
    b.getCurrentPlayer()->addBuys(1);
    b.getCurrentPlayer()->addCoins(2);
}

bool Festival::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}