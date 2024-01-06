#include "Mill.hpp"
#include "../game/Board.hpp"

Mill::Mill(): Card(4, kEnumToString(KingdomCardName::Mill), true),
                Action(4, kEnumToString(KingdomCardName::Mill), true),
                Victory(4, kEnumToString(KingdomCardName::Mill), true, 1) {}

/*!
//! Jouer la carte Moulin: +1 carte, +1 action, peut permettre de défausser 2 cartes pour +2 pièces.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Mill::play(Board &b) {
    Player *p = b.getCurrentPlayer();
    p->getNewCardFromDeck();
    p->addActions(1);

    std::string choice = "";
    while(choice == "" || (choice != "Y" && choice != "N")) {

        std::cout << p << std::endl;
        std::cout << p->getUsername() << ", would you like to discard 2 cards in exchange of +2 coins (Y/N)?: ";
        std::cin >> choice;
    }

    if(choice == "Y") {
        int cardDiscarded = 0;

        int cardIndex = -2;
        while(cardDiscarded < 2 || (cardIndex < 0 || cardIndex > p->getNbCardsInHand()-1)) {
            if(cardDiscarded == 2 || p->getNbCardsInHand() == 0) {
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

            if(0 <= cardIndex && cardIndex <= p->getNbCardsInHand()-1) {
                Card *c = p->showCard(cardIndex);
                if(c != NULL) {
                    if(p->discardCard(cardIndex)) {
                        cardDiscarded++;
                    }
                }
            }
        }

        if(cardDiscarded == 2) {
            p->addCoins(2);
        }
    }
}

/*!
//! Gagner avec la carte Moulin: +1 point de victoire.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Mill::setVictoryPoints(Board &b) {
    b.getCurrentPlayer()->addVictoryPoints(this->getNumberPoints());
}

bool Mill::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}