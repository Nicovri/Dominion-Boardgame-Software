#include "Sentry.hpp"
#include "../game/Board.hpp"

Sentry::Sentry(): Action(5, kEnumToString(KingdomCardName::Sentry), true) {}

/*!
//! Jouer la carte Sentinelle: +1 carte, +1 action, regarde les 2 premières cartes du deck, écarte et/ou défausse puis replace le reste sur le deck.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Sentry::play(Board &b) {
    Player *p = b.getCurrentPlayer();

    p->getNewCardFromDeck();
    p->addActions(1);

    std::vector<Card*> cardsToCheck = p->showCardsInDeck(2);

    int choice1;
    int choice2;

    int i = 0;
    for(Card *c : cardsToCheck) {
        std::cout << std::endl << "Card " << c << std::endl;
        i++;

        int choice = -1;
        while (choice < 0 || choice > 2) {
            std::cout << p->getUsername() << ", what would you like to do with this card?" << std::endl;
            std::cout << "0: Trash it\n1: Discard it\n2: Place it back in the deck" << std::endl;
            std::cout << "Your choice: ";
            std::cin >> choice;

            if(std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                choice = -1;
            }
        }
        i == 1 ? choice1 = choice : choice2 = choice;
    }

    if(choice1 == 0) {
        p->trashCardsInDeck(1);
    } else if(choice1 == 1) {
        p->addCardsFromDeckToDiscard(1);
    } else if(choice1 == 2) {
        p->getNewCardFromDeck();
    }

    if(choice2 == 0) {
        p->trashCardsInDeck(1);
    } else if(choice2 == 1) {
        p->addCardsFromDeckToDiscard(1);
    } else if(choice2 == 2) {
        p->getNewCardFromDeck();
    }

    if((choice1 == 2 && choice2 != 2) || (choice2 == 2 && choice1 != 2)) {
        p->addCardFromHandToDeck(p->getNbCardsInHand()-1);
    }

    if(choice1 == 2 && choice2 == 2) {
        int choice = -1;
        while (choice < 0 || choice > 1) {
            std::cout << std::endl << p->getUsername() << ", which card would you like to put back on your deck first?" << std::endl;
            std::cout << "0: " << cardsToCheck.at(0) << std::endl << "1: " << cardsToCheck.at(1) << std::endl;
            std::cout << "Your choice: ";
            std::cin >> choice;

            if(std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                choice = -1;
            }
        }

        if(choice == 0) {
            p->addCardFromHandToDeck(p->getNbCardsInHand()-2);
            p->addCardFromHandToDeck(p->getNbCardsInHand()-1);
        } else if(choice == 1) {
            p->addCardFromHandToDeck(p->getNbCardsInHand()-1);
            p->addCardFromHandToDeck(p->getNbCardsInHand()-1);
        }
    }
}

bool Sentry::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}