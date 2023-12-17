#include "Curse.hpp"
#include "../game/Board.hpp"

Curse::Curse(): Victory(0, "Curse", true, -1) {}

void Curse::play(Board &b) {
    b.getCurrentPlayer()->addVictoryPoints(this->getNumberPoints());
}