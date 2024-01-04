#include "TradingPost.hpp"
#include "../game/Board.hpp"

TradingPost::TradingPost(): Card(5, kEnumToString(KingdomCardName::TradingPost), true),
                            Action(5, kEnumToString(KingdomCardName::TradingPost), true) {}

/*!
//! Jouer la carte Comptoir: permet d'écarter 2 cartes de la main du joueur en échange d'un Argent directement dans la main.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void TradingPost::play(Board &b) {
    Player *p = b.getCurrentPlayer();

    std::string choice = "";
    while(choice == "" || (choice != "Y" && choice != "N")) {

        std::cout << p << std::endl;
        std::cout << p->getUsername() << ", would you like to trash 2 cards in exchange of a Silver to your hand (Y/N)?: ";
        std::cin >> choice;
    }

    if(choice == "Y") {
        int cardTrashed = 0;

        int cardIndex = -2;
        while(cardTrashed < 2 || (cardIndex < 0 || cardIndex > p->getNbCardsInHand()-1)) {
            if(cardTrashed == 2 || p->getNbCardsInHand() == 0) {
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

            Card *c = p->showCard(cardIndex);
            if(c != NULL) {
                if(p->trashCard(cardIndex)) {
                    cardTrashed++;
                }
            }
        }

        if(cardTrashed == 2) {
            Card *c2 = b.chooseCard("Silver");
            if(c2 != NULL) {
                p->getNewCardInHand(c2, true);
            }
        }
    }
}

bool TradingPost::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}