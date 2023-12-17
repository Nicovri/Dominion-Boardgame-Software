#include "Duchy.hpp"
#include "../game/Board.hpp"

Duchy::Duchy(): Victory(5, "Duchy", true, 3) {}

void Duchy::play(Board &b) {
    b.getCurrentPlayer()->addVictoryPoints(this->getNumberPoints());
}