#include "Village.hpp"
#include "../game/Board.hpp"

Village::Village(): Action(3, "Village", true) {}

void Village::play(Board &b) {
    b.getCurrentPlayer()->getNewCardFromDeck();
    b.getCurrentPlayer()->addActions(2);
}

bool Village::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}