#include "Silver.hpp"
#include "../game/Board.hpp"

Silver::Silver(): Card(3, oEnumToString(OtherCardName::Silver), true),
                    Treasure(3, oEnumToString(OtherCardName::Silver), true, 2) {}

/*!
//! Jouer la carte Argent: +2 point de victoire.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Silver::play(Board &b) {
    b.getCurrentPlayer()->addCoins(this->getNumberPoints());
}