#include "Province.hpp"
#include "../game/Board.hpp"

Province::Province(): Victory(8, "Province", true, 6) {}

void Province::play(Board &b) {
    b.getCurrentPlayer()->addVictoryPoints(this->getNumberPoints());
}