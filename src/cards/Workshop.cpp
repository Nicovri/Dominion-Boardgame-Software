#include "Workshop.hpp"
#include "../game/Board.hpp"

Workshop::Workshop(): Card(3, kEnumToString(KingdomCardName::Workshop), true),
                        Action(3, kEnumToString(KingdomCardName::Workshop), true, "Which card would you like to choose?") {}

/*!
//! Jouer la carte Atelier: fait gagner une carte coûtant jusqu'à 4 pièces.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Workshop::play(Board &b) {
    Card * c = b.chooseCard(4, true);
    if(c != NULL) {
        b.getCurrentPlayer()->getNewCard(c, true);
    }
}

bool Workshop::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    cardIndexInHand = cardIndexInHand;
    if(repetitiveActionCounter == 1) {
        Card * c = b.chooseCard(4, pileIndex);
        if(c != NULL) {
            b.getCurrentPlayer()->getNewCard(c, true);
        }
        return true;
    }
    return false;
}