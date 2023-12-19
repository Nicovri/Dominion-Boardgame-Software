#include "Remodel.hpp"
#include "../game/Board.hpp"

Remodel::Remodel(): Action(4, "Remodel", true) {}

void Remodel::play(Board &b) {
    Player *p = b.getCurrentPlayer();
    int allowedPrice = -1;

    int cardIndex = -2;
    while(cardIndex < -1 || cardIndex > p->getNbCardsInHand()-1) {

        std::cout << p << std::endl;
        std::cout << p->getUsername() << ", which card would you like to trash (in exchange of another card costing up to 2Coins more)?: ";
        std::cin >> cardIndex;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cardIndex = -2;
        }
        if(cardIndex == -1) {
            break;
        } else {
            allowedPrice = p->showCard(cardIndex)->getPrice() + 2;
            if(!p->trashCard(cardIndex)) {
                allowedPrice = -1;
            }
            break;
        }
        cardIndex = -2;
    }

    
    b.displayFilteredPiles([allowedPrice](const Pile p) { return !p.isEmpty() && p.showCard(0)->getPrice() <= allowedPrice; });

    Card *c = b.chooseCard(allowedPrice, true);
    p->getNewCard(c, true);
}