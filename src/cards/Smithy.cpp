#include "Smithy.hpp"
#include "../game/Board.hpp"

Smithy::Smithy(): Action(4, "Smithy", true) {}

void Smithy::play(Board &b) {
    b.getCurrentPlayer()->getNewCardsFromDeck(3);
}