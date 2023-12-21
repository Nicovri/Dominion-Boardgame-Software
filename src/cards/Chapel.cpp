#include "Chapel.hpp"
#include "../game/Board.hpp"

Chapel::Chapel(): Action(2, "Chapel", true) {}

void Chapel::play(Board &b) {
    Player *p = b.getCurrentPlayer();

    int cardIndex = -2;
    int counterTrashed = 0;
    while(cardIndex < -1 || cardIndex > p->getNbCardsInHand()-1) {
        if(p->getNbCardsInHand() == 0) {
            break;
        }

        if(counterTrashed == 4) {
            break;
        }

        std::cout << p << std::endl;
        std::cout << p->getUsername() << ", which card would you like to trash?: ";
        std::cin >> cardIndex;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cardIndex = -2;
        }
        if(cardIndex == -1) {
            break;
        } else {
            if(p->trashCard(cardIndex)) {
                counterTrashed++;
            }
        }
        cardIndex = -2;
    }
}