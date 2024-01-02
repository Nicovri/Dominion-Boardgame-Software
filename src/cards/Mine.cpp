#include "Mine.hpp"
#include "../game/Board.hpp"

Mine::Mine(): Card(5, kEnumToString(KingdomCardName::Mine), true),
                Action(5, kEnumToString(KingdomCardName::Mine), true, "Which Treasure card would you like to trash and which Treasure card would you like to get (up to 3 coins more)?") {}

/*!
//! Jouer la carte Mine: écarte une carte Trésor de la main, reçoit une carte Trésor dans la main coûtant jusqu'à 3 pièces de plus.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Mine::play(Board &b) {
    Player *p = b.getCurrentPlayer();
    int allowedPrice = -1;

    if(!p->hasTreasureCards()) {
        return;
    }

    int cardIndex = -2;
    while(cardIndex < -1 || cardIndex > p->getNbCardsInHand()-1 ||
            (0 <= cardIndex  && cardIndex <= p->getNbCardsInHand()-1 && !p->showCard(cardIndex)->isTreasureCard())) {

        std::cout << p << std::endl;
        std::cout << p->getUsername() << ", which Treasure card would you like to trash (in exchange of another Treasure card costing up to 3 Coins more going directly into your hand)?: ";
        std::cin >> cardIndex;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cardIndex = -2;
        }
        if(cardIndex == -1) {
            return;
        } else {
            Card *c = p->showCard(cardIndex);
            if(c != NULL) {
                if(c->isTreasureCard()) {
                    allowedPrice = p->showCard(cardIndex)->getPrice() + 3;
                    if(!p->trashCard(cardIndex)) {
                        allowedPrice = -1;
                    } else {
                        break;
                    }
                }
            }
        }
        cardIndex = -2;
    }

    
    // b.displayFilteredPiles([allowedPrice](const Pile p) { return !p.isEmpty() && p.showCard(0)->isTreasureCard() && p.showCard(0)->getPrice() <= allowedPrice; });

    Card *c = b.chooseCard(allowedPrice, true);
    while(!c->isTreasureCard()) {
        c = b.chooseCard(allowedPrice, true);
    }
    p->getNewCardInHand(c, true);
}

bool Mine::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    if(repetitiveActionCounter == 1) {
        if(b.getCurrentPlayer()->showCard(cardIndexInHand)->isTreasureCard()) {
            int allowedPrice = b.getCurrentPlayer()->showCard(cardIndexInHand)->getPrice() + 3;
            if(!b.getCurrentPlayer()->trashCard(cardIndexInHand)) {
                allowedPrice = -1;
            }
            Card * c = b.chooseCard(allowedPrice, pileIndex);
            if(c != NULL) {
                b.getCurrentPlayer()->getNewCardInHand(c, true);
            }
            return true;
        }
    }
    return false;
}