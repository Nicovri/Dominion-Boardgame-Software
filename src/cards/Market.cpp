#include "Market.hpp"
#include "../game/Board.hpp"

Market::Market(): Action(5, "Market", true) {}

void Market::play(Board &b) {
    b.getCurrentPlayer()->getNewCardFromDeck();
    b.getCurrentPlayer()->addActions(1);
    b.getCurrentPlayer()->addBuys(1);
    b.getCurrentPlayer()->addCoins(1);
}

bool Market::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}