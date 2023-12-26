#include "Cellar.hpp"
#include "../game/Board.hpp"

Cellar::Cellar(): Action(2, "Cellar", true, "Which card would you like to discard?") {}

void Cellar::play(Board &b) {
    Player *p = b.getCurrentPlayer();
    p->addActions(1);

    int cardIndex = -2;
    int counterDiscarded = 0;
    while(cardIndex < -1 || cardIndex > p->getNbCardsInHand()-1) {
        if(p->getNbCardsInHand() == 0) {
            break;
        }

        std::cout << p << std::endl;
        std::cout << p->getUsername() << ", which card would you like to discard?: ";
        std::cin >> cardIndex;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cardIndex = -2;
        }
        if(cardIndex == -1) {
            break;
        } else {
            if(p->discardCard(cardIndex)) {
                counterDiscarded++;
            }
        }
        cardIndex = -2;
    }
    
    p->getNewCardsFromDeck(counterDiscarded);
}

bool Cellar::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}