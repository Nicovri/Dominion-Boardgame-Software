#include "Artisan.hpp"
#include "../game/Board.hpp"

Artisan::Artisan(): Card(6, kEnumToString(KingdomCardName::Artisan), true),
                    Action(6, kEnumToString(KingdomCardName::Artisan), true) {}

/*!
//! Jouer la carte Artisan: fait gagner une carte coûtant jusqu'à 5 pièces dans la main du joueur, place une carte de la main sur le deck.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Artisan::play(Board &b) {
    Player *p = b.getCurrentPlayer();

    int allowedPrice = 5;
    
    Card *c = b.chooseCard(allowedPrice, true);
    if(c != NULL) {
        p->getNewCardInHand(c, true);
    }

    int cardIndex = -2;
    while(cardIndex < 0 || cardIndex > p->getNbCardsInHand()-1) {

        std::cout << p << std::endl;
        std::cout << p->getUsername() << ", which card would you like to put onto your deck?: ";
        std::cin >> cardIndex;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cardIndex = -2;
        }

        if(!p->addCardFromHandToDeck(cardIndex)) {
            cardIndex = -2;
        } else {
            return;
        }
    }
}

bool Artisan::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}