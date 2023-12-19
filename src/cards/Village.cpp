#include "Village.hpp"
#include "../game/Board.hpp"

Village::Village(): Action(3, "Village", true) {}

void Village::play(Board &b) {
    b.getCurrentPlayer()->getNewCardFromDeck();
    b.getCurrentPlayer()->addActions(2);
}