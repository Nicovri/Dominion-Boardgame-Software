#include "Vassal.hpp"
#include "../game/Board.hpp"

Vassal::Vassal(): Card(3, kEnumToString(KingdomCardName::Vassal), true),
                    Action(3, kEnumToString(KingdomCardName::Vassal), true) {}

/*!
//! Jouer la carte Vassal: +2 pièces, défausse la carte du dessus du deck, peut utiliser son effet si il s'agit d'une carte Action.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Vassal::play(Board &b) {
    Player *p = b.getCurrentPlayer();

    p->addCoins(2);

    Card *c = NULL;
    if(!p->showCardsInDeck(1).empty()) {
        c = p->showCardsInDeck(1).at(0);
    }

    if(c != NULL) {

        if(c->isActionCard()) {
            std::string choice = "";
            while(choice == "" || (choice != "Y" && choice != "N")) {

                std::cout << p->getUsername() << ", would you like to play this Action card: " << c->getTitle() << " (Y/N)?: ";
                std::cin >> choice;
            }

            if(choice == "Y") {
                p->addCardsFromDeckToDiscard(1);
                c->play(b);
            }
        } else {
            p->addCardsFromDeckToDiscard(1);
        }
    }
}

bool Vassal::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}