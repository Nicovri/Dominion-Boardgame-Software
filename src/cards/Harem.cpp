#include "Harem.hpp"
#include "../game/Board.hpp"

Harem::Harem(): Card(6, kEnumToString(KingdomCardName::Harem), true),
                Treasure(6, kEnumToString(KingdomCardName::Harem), true, 2),
                Victory(6, kEnumToString(KingdomCardName::Harem), true, 2) {}

/*!
//! Jouer la carte Harem: +2 pièces.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Harem::play(Board &b) {
    b.getCurrentPlayer()->addCoins(Treasure::getNumberPoints());
}

/*!
//! Gagner avec la carte Harem: +2 points de victoire.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Harem::setVictoryPoints(Board &b) {
    b.getCurrentPlayer()->addVictoryPoints(Victory::getNumberPoints());
}