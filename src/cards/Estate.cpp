#include "Estate.hpp"
#include "../game/Board.hpp"

Estate::Estate(): Victory(2, "Estate", true, 1) {}

void Estate::play(Board &b) {
    b.getCurrentPlayer()->addVictoryPoints(this->getNumberPoints());
}