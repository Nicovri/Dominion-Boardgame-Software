#include "Witch.hpp"
#include "../game/Board.hpp"

Witch::Witch(): Action(5, kEnumToString(KingdomCardName::Witch), true) {}

/*!
//! Jouer la carte Sorcière: +2 cartes, chaque autre joueur gagne une Malédiction.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Witch::play(Board &b) {
    Player *cp = b.getCurrentPlayer();
    cp->getNewCardsFromDeck(2);
    for(Player *p : b.getPlayers()) {
        if(p != cp) {
            p->getNewCard(b.chooseCard("Curse"), true);
        }
    }
}

bool Witch::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}