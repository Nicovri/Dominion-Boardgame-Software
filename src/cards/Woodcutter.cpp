#include "Woodcutter.hpp"
#include "../game/Board.hpp"

Woodcutter::Woodcutter(): Card(3, kEnumToString(KingdomCardName::Woodcutter), true),
                            Action(3, kEnumToString(KingdomCardName::Woodcutter), true) {}

/*!
//! Jouer la carte Bûcheron: +1 achat, +2 pièces.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Woodcutter::play(Board &b) {
    b.getCurrentPlayer()->addBuys(1);
    b.getCurrentPlayer()->addCoins(2);
}

bool Woodcutter::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}