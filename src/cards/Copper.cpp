#include "Copper.hpp"
#include "../game/Board.hpp"

Copper::Copper(): Treasure(0, oEnumToString(OtherCardName::Copper), true, 1) {}

/*!
//! Jouer la carte Cuivre: +1 pièce.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Copper::play(Board &b) {
    b.getCurrentPlayer()->addCoins(this->getNumberPoints());
}