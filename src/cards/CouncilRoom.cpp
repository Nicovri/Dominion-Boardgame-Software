#include "CouncilRoom.hpp"
#include "../game/Board.hpp"

CouncilRoom::CouncilRoom(): Card(5, kEnumToString(KingdomCardName::CouncilRoom), true),
                            Action(5, kEnumToString(KingdomCardName::CouncilRoom), true) {}

/*!
//! Jouer la carte Chambre Du Conseil: +4 cartes, +1 achat, chaque autre joueur pioche une carte de son deck.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void CouncilRoom::play(Board &b) {
    Player *cp = b.getCurrentPlayer();
    cp->getNewCardsFromDeck(4);
    cp->addBuys(1);
    for(Player *p : b.getPlayers()) {
        if(p != cp) {
            p->getNewCardFromDeck();
        }
    }
}

bool CouncilRoom::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}