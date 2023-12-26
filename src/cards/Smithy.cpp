#include "Smithy.hpp"
#include "../game/Board.hpp"

Smithy::Smithy(): Action(4, "Smithy", true) {}

void Smithy::play(Board &b) {
    b.getCurrentPlayer()->getNewCardsFromDeck(3);
}

bool Smithy::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}