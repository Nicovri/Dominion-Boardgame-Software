#include "Curse.hpp"
#include "../game/Board.hpp"

Curse::Curse(): Card(0, oEnumToString(OtherCardName::Curse), true),
                Victory(0, oEnumToString(OtherCardName::Curse), true, -1) {}

/*!
//! Jouer la carte Malédiction: -1 point de victoire.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Curse::play(Board &b) {
    b.getCurrentPlayer()->addVictoryPoints(this->getNumberPoints());
}