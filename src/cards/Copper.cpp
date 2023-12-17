#include "Copper.hpp"
#include "../game/Board.hpp"

Copper::Copper(): Treasure(0, "Copper", true, 1) {}

void Copper::play(Board &b) {
    b.getCurrentPlayer()->addCoins(this->getNumberPoints());
}