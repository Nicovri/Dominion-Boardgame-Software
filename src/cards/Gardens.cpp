#include "Gardens.hpp"
#include "../game/Board.hpp"

Gardens::Gardens(): Card(4, kEnumToString(KingdomCardName::Gardens), true),
                    Victory(4, kEnumToString(KingdomCardName::Gardens), true, 1) {}

void Gardens::play([[maybe_unused]] Board &b) {}

/*!
//! Gagner avec la carte Jardins: +1 points de victoire par tranche de 10 cartes.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Gardens::setVictoryPoints(Board &b) {
    Player *p = b.getCurrentPlayer();
    p->addVictoryPoints(this->getNumberPoints() * (p->getNbCardsTotal() / 10));
}