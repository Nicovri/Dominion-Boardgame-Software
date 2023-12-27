#include "Market.hpp"
#include "../game/Board.hpp"

Market::Market(): Action(5, kEnumToString(KingdomCardName::Market), true) {}

/*!
//! Jouer la carte Marché: +1 carte, +1 action, +1 achat, +1 pièce.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Market::play(Board &b) {
    b.getCurrentPlayer()->getNewCardFromDeck();
    b.getCurrentPlayer()->addActions(1);
    b.getCurrentPlayer()->addBuys(1);
    b.getCurrentPlayer()->addCoins(1);
}

bool Market::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}