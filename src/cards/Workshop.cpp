#include "Workshop.hpp"
#include "../game/Board.hpp"

Workshop::Workshop(): Action(3, "Workshop", true) {}

void Workshop::play(Board &b) {
    Card * c = b.chooseCard(4, true);
    if(c != NULL) {
        b.getCurrentPlayer()->getNewCard(c, true);
    }
}