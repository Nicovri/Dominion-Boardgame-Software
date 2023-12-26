#include "Workshop.hpp"
#include "../game/Board.hpp"

Workshop::Workshop(): Action(3, "Workshop", true, "Which card would you like to choose?") {}

void Workshop::play(Board &b) {
    Card * c = b.chooseCard(4, true);
    if(c != NULL) {
        b.getCurrentPlayer()->getNewCard(c, true);
    }
}

bool Workshop::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    cardIndexInHand = cardIndexInHand;
    if(repetitiveActionCounter == 1) {
        Card * c = b.chooseCard(4, pileIndex);
        if(c != NULL) {
            b.getCurrentPlayer()->getNewCard(c, true);
        }
        return true;
    }
    return false;
}