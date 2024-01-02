#include "Gold.hpp"
#include "../game/Board.hpp"

Gold::Gold(): Card(6, oEnumToString(OtherCardName::Gold), true),
                Treasure(6, oEnumToString(OtherCardName::Gold), true, 3) {}

/*!
//! Jouer la carte Or: +3 pièces.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Gold::play(Board &b) {
    b.getCurrentPlayer()->addCoins(this->getNumberPoints());
}