#include "Silver.hpp"
#include "../game/Board.hpp"

Silver::Silver(): Treasure(3, "Silver", true, 2) {}

void Silver::play(Board &b) {
    b.getCurrentPlayer()->addCoins(this->getNumberPoints());
}