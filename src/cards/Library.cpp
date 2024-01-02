#include "Library.hpp"
#include "../game/Board.hpp"

Library::Library(): Card(5, kEnumToString(KingdomCardName::Library), true),
                    Action(5, kEnumToString(KingdomCardName::Library), true) {}

/*!
//! Jouer la carte Bibliothèque: pioche jusqu'à avoir 7 cartes dans la main. Chaque carte action piochée peut être mise de côté et défaussée.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Library::play(Board &b) {
    Player *p = b.getCurrentPlayer();

    std::vector<Card*> actionsToDiscardAfterwards = {};

    while(p->getNbCardsInHand() < 7 || (p->getNbCardsInDeck() == 0 && p->getNbCardsInDiscard() == 0)) {
        Card *c = NULL;
        if(!p->showCardsInDeck(1).empty()) {
            c = p->showCardsInDeck(1).at(0);
        }

        if(c != NULL) {
            if(c->isActionCard()) {
                std::string choice = "";
                while(choice == "" || (choice != "Y" && choice != "N")) {

                    std::cout << p->getUsername() << ", would you like to draw this Action card: " << c->getTitle() << " (Y/N)?: ";
                    std::cin >> choice;
                }

                if(choice == "Y") {
                    p->getNewCardFromDeck();
                } else {
                    Card *c = p->getTopCardFromDeck();
                    if(c != NULL) {
                        actionsToDiscardAfterwards.push_back(c);
                    }
                }
            } else {
                p->getNewCardFromDeck();
            }
        } else {
            p->getDeckFromDiscard();
        }
    }

    for(Card *c : actionsToDiscardAfterwards) {
        p->getNewCard(c, true);
    }
}

bool Library::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}