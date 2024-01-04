#include "Steward.hpp"
#include "../game/Board.hpp"

Steward::Steward(): Card(3, kEnumToString(KingdomCardName::Steward), true),
                    Action(3, kEnumToString(KingdomCardName::Steward), true) {}

/*!
//! Jouer la carte Intendant: Choisir une option: +2 cartes, ou +2 pièces, ou écarter 2 cartes de la main du joueur.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Steward::play(Board &b) {
    Player *p = b.getCurrentPlayer();

    int effectChosen = -1;

    std::cout << "\nWhat effect do you want to play?\n0: +2 cards\n1: +2 coins\n2: trash 2 cards from your hand" << std::endl;
    while(effectChosen < 0 || effectChosen > 2) {
        std::cout << "Your choice: ";
        std::cin >> effectChosen;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            effectChosen = -1;
        }
    }

    if(effectChosen == 0) {
        p->getNewCardsFromDeck(2);
    }

    else if(effectChosen == 1) {
        p->addCoins(2);
    }

    else if(effectChosen == 2) {
        int cardTrashed = 0;

        int cardIndex = -2;
        while(cardTrashed < 2 || (cardIndex < 0 || cardIndex > p->getNbCardsInHand()-1)) {
            if(cardTrashed == 2 || p->getNbCardsInHand() == 0) {
                return;
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
    }
}

bool Steward::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}