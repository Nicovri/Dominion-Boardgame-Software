#include "Witch.hpp"
#include "../game/Board.hpp"

Witch::Witch(): Action(5, "Witch", true) {}

void Witch::play(Board &b) {
    Player *cp = b.getCurrentPlayer();
    cp->getNewCardsFromDeck(2);
    for(Player *p : b.getPlayers()) {
        if(p != cp) {
            p->getNewCard(b.chooseCard("Curse"), true);
        }
    }
}