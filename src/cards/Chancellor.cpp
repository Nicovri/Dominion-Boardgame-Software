#include "Chancellor.hpp"
#include "../game/Board.hpp"

Chancellor::Chancellor(): Action(3, kEnumToString(KingdomCardName::Chancellor), true) {}

/*!
//! Jouer la carte Chancelier: +2 pièces, permet de défausser son deck.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Chancellor::play(Board &b) {
    Player *p = b.getCurrentPlayer();

    p->addCoins(2);

    std::string choice = "";

    while(choice == "" || (choice != "Y" && choice != "N")) {

        std::cout << p->getUsername() << ", would you like to discard your deck (Y/N)?: ";
        std::cin >> choice;
    }

    if(choice == "Y") {
        p->addCardsFromDeckToDiscard(p->getNbCardsInDeck());
    }
}

bool Chancellor::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}