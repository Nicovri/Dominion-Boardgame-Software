#include "Mine.hpp"
#include "../game/Board.hpp"

Mine::Mine(): Action(5, "Mine", true) {}

void Mine::play(Board &b) {
    Player *p = b.getCurrentPlayer();
    int allowedPrice = -1;

    if(p->hasTreasureCards()) {
        int cardIndex = -2;
        while(cardIndex < -1 || cardIndex > p->getNbCardsInHand()-1 ||
                (0 <= cardIndex  && cardIndex <= p->getNbCardsInHand()-1 && !p->showCard(cardIndex)->isTreasureCard())) {

            std::cout << p << std::endl;
            std::cout << p->getUsername() << ", which Treasure card would you like to trash (in exchange of another Treasure card costing up to 3Coins more going directly into your hand)?: ";
            std::cin >> cardIndex;

            if(std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cardIndex = -2;
            }
            if(cardIndex == -1) {
                break;
            } else {
                if(p->showCard(cardIndex)->isTreasureCard()) {
                    allowedPrice = p->showCard(cardIndex)->getPrice() + 3;
                    if(!p->trashCard(cardIndex)) {
                        allowedPrice = -1;
                    }
                    break;
                }
            }
            cardIndex = -2;
        }

    
        b.displayFilteredPiles([allowedPrice](const Pile p) { return !p.isEmpty() && p.showCard(0)->isTreasureCard() && p.showCard(0)->getPrice() <= allowedPrice; });

        Card *c = b.chooseCard(allowedPrice, true);
        while(!c->isTreasureCard()) {
            c = b.chooseCard(allowedPrice, true);
        }
        p->getNewCard(c, true, true);
    }
}