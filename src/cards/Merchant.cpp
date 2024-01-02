#include "Merchant.hpp"
#include "../game/Board.hpp"

Merchant::Merchant(): Card(3, kEnumToString(KingdomCardName::Merchant), true),
                        Action(3, kEnumToString(KingdomCardName::Merchant), true) {}

/*!
//! Jouer la carte Marchand: +1 carte, +1 action, la prochaine fois qu'un Argent est joué +1 pièce.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Merchant::play(Board &b) {
    Player *p = b.getCurrentPlayer();

    p->getNewCardFromDeck();
    p->addActions(1);
    
    // TODO fonctionne dans les cas simples, mais il peut arriver de jouer une autre carte Action après celle-ci qui va ajouter de nouvelles cartes à la main (dont des cartes Argent)... Comment faire (ajout d'une variable dans la classe Player?) ?
    // Cartes dans la durée compliquées à implémenter avec la configuration actuelle
    for(int i = 0; i < p->getNbCardsInHand(); i++) {
        if(p->showCard(i)->getTitle() == oEnumToString(OtherCardName::Silver)) {
            p->addCoins(1);
            break;
        }
    }
}

bool Merchant::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}