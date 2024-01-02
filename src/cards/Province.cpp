#include "Province.hpp"
#include "../game/Board.hpp"

Province::Province(): Card(8, oEnumToString(OtherCardName::Province), true),
                        Victory(8, oEnumToString(OtherCardName::Province), true, 6) {}

/*!
//! Jouer la carte Province: +6 points de victoire.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Province::play(Board &b) {
    b.getCurrentPlayer()->addVictoryPoints(this->getNumberPoints());
}