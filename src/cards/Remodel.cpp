#include "Remodel.hpp"
#include "../game/Board.hpp"

Remodel::Remodel(): Action(4, kEnumToString(KingdomCardName::Remodel), true, "Which card would you like to trash and which card would you like to get (up to 2 coins more)?") {}

/*!
//! Jouer la carte Rénovation: écarte une carte de la main, fait gagner une carte coûtant jusqu'à 2 pièces de plus.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Remodel::play(Board &b) {
    Player *p = b.getCurrentPlayer();
    int allowedPrice = -1;

    int cardIndex = -2;
    while(cardIndex < -1 || cardIndex > p->getNbCardsInHand()-1) {

        std::cout << p << std::endl;
        std::cout << p->getUsername() << ", which card would you like to trash (in exchange of another card costing up to 2 Coins more)?: ";
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

    
    Card *c = b.chooseCard(allowedPrice, true);
    if(c != NULL) {
        p->getNewCard(c, true);
    }
}

bool Remodel::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    if(repetitiveActionCounter == 1) {
        int allowedPrice = b.getCurrentPlayer()->showCard(cardIndexInHand)->getPrice() + 2;
        if(!b.getCurrentPlayer()->trashCard(cardIndexInHand)) {
            allowedPrice = -1;
        }
        Card * c = b.chooseCard(allowedPrice, pileIndex);
        if(c != NULL) {
            b.getCurrentPlayer()->getNewCard(c, true);
        }
        return true;
    }
    return false;
}