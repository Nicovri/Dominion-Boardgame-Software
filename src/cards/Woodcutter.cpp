#include "Woodcutter.hpp"
#include "../game/Board.hpp"

Woodcutter::Woodcutter(): Action(3, "Woodcutter", true) {}

void Woodcutter::play(Board &b) {
    b.getCurrentPlayer()->addBuys(1);
    b.getCurrentPlayer()->addCoins(2);
}

bool Woodcutter::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}