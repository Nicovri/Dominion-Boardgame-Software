#include "Estate.hpp"
#include "../game/Board.hpp"

Estate::Estate(): Victory(2, oEnumToString(OtherCardName::Estate), true, 1) {}

/*!
//! Jouer la carte Domaine: +1 point de victoire.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Estate::play(Board &b) {
    b.getCurrentPlayer()->addVictoryPoints(this->getNumberPoints());
}