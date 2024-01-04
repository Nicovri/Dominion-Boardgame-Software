#include "Estate.hpp"
#include "../game/Board.hpp"

Estate::Estate(): Card(2, oEnumToString(OtherCardName::Estate), true),
                    Victory(2, oEnumToString(OtherCardName::Estate), true, 1) {}

void Estate::play([[maybe_unused]] Board &b) {}

/*!
//! Gagner avec la carte Domaine: +1 point de victoire.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Estate::setVictoryPoints(Board &b) {
    b.getCurrentPlayer()->addVictoryPoints(this->getNumberPoints());
}