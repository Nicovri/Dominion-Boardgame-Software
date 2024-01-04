#include "Curse.hpp"
#include "../game/Board.hpp"

Curse::Curse(): Card(0, oEnumToString(OtherCardName::Curse), true),
                Victory(0, oEnumToString(OtherCardName::Curse), true, -1) {}

void Curse::play([[maybe_unused]] Board &b) {}

/*!
//! Gagner avec la carte Malédiction: -1 point de victoire.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Curse::setVictoryPoints(Board &b) {
    b.getCurrentPlayer()->addVictoryPoints(this->getNumberPoints());
}