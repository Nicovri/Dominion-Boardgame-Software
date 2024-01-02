#include "Duchy.hpp"
#include "../game/Board.hpp"

Duchy::Duchy(): Card(5, oEnumToString(OtherCardName::Duchy), true),
                Victory(5, oEnumToString(OtherCardName::Duchy), true, 3) {}

/*!
//! Jouer la carte Duché: +3 points de victoire.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Duchy::play(Board &b) {
    b.getCurrentPlayer()->addVictoryPoints(this->getNumberPoints());
}