#include "Village.hpp"
#include "../game/Board.hpp"

Village::Village(): Action(3, kEnumToString(KingdomCardName::Village), true) {}

/*!
//! Jouer la carte Village: +1 carte, +2 actions.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Village::play(Board &b) {
    b.getCurrentPlayer()->getNewCardFromDeck();
    b.getCurrentPlayer()->addActions(2);
}

bool Village::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}