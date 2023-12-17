#include "Gold.hpp"
#include "../game/Board.hpp"

Gold::Gold(): Treasure(6, "Gold", true, 3) {}

void Gold::play(Board &b) {
    b.getCurrentPlayer()->addCoins(this->getNumberPoints());
}