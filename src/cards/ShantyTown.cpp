#include "ShantyTown.hpp"
#include "../game/Board.hpp"

ShantyTown::ShantyTown(): Card(3, kEnumToString(KingdomCardName::ShantyTown), true),
                            Action(3, kEnumToString(KingdomCardName::ShantyTown), true) {}

/*!
//! Jouer la carte Taudis: +2 actions, révèle la main du joueur et si elle ne contient aucune carte Action, +2 cartes.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void ShantyTown::play(Board &b) {
    Player *p = b.getCurrentPlayer();

    p->addActions(2);

    if(!p->hasActionCards()) {
        p->getNewCardsFromDeck(2);
    }
}

bool ShantyTown::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}