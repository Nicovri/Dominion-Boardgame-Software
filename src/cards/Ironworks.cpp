#include "Ironworks.hpp"
#include "../game/Board.hpp"

Ironworks::Ironworks(): Card(4, kEnumToString(KingdomCardName::Ironworks), true),
                        Action(4, kEnumToString(KingdomCardName::Ironworks), true) {}

/*!
//! Jouer la carte Fonderie: fait gagner une carte coûtant jusqu'à 4 pièces. Si c'est une carte Action, +1 action. Si c'est une carte Trésor, +1 pièce. Si c'est une carte Victoire, +1 carte.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Ironworks::play(Board &b) {
    Card * c = b.chooseCard(4, true);
    if(c != NULL) {
        b.getCurrentPlayer()->getNewCard(c, true);

        if(c->isActionCard()) {
            b.getCurrentPlayer()->addActions(1);
        }

        if(c->isTreasureCard()) {
            b.getCurrentPlayer()->addCoins(1);
        }

        if(c->isVictoryCard()) {
            b.getCurrentPlayer()->getNewCardFromDeck();
        }
    }
}

bool Ironworks::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}