#include "Lurker.hpp"
#include "../game/Board.hpp"

Lurker::Lurker(): Card(2, kEnumToString(KingdomCardName::Lurker), true),
                    Action(2, kEnumToString(KingdomCardName::Lurker), true) {}

/*!
//! Jouer la carte Rôdeur: +1 action, choisir une option: jeter une carte Action d'une pile du plateau, ou gagner une carte Action du rebut.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Lurker::play(Board &b) {
    Player *p = b.getCurrentPlayer();

    p->addActions(1);

    int effectChosen = -1;

    std::cout << "\nWhat effect do you want to play?\n0: trash an Action card from the Supply\n1: gain an Action card from the trash" << std::endl;
    while(effectChosen < 0 || effectChosen > 1) {
        std::cout << "Your choice: ";
        std::cin >> effectChosen;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            effectChosen = -1;
        }
    }

    if(effectChosen == 0) {
        Card *c = b.chooseCard(100, true);
        while(!c->isActionCard()) {
            c = b.chooseCard(100, true);
        }
        p->getNewCardInHand(c, true);
        p->trashCard(p->getNbCardsInHand()-1);
    }

    else if(effectChosen == 1) {
        std::vector<Card*> trashCards = b.showCardsInTrash(b.getNbCardsInTrash());

        if(trashCards.empty()) {
            return;
        }

        bool hasActionCards = false;
        for(Card *c : trashCards) {
            if(c->isActionCard()) {
                hasActionCards = true;
                break;
            }
        }

        if(hasActionCards) {
            int i = 0;
            for(Card *c : trashCards) {
                std::cout << i << ": " << c << std::endl;
                i++;
            }

            int cardIndex = -2;
            while(cardIndex < 0 || cardIndex > int(trashCards.size())-1 ||
                    (0 <= cardIndex  && cardIndex <= int(trashCards.size())-1 && !trashCards.at(cardIndex)->isActionCard())) {

                std::cout << p->getUsername() << ", which Action card from the trash would you like to get?: ";
                std::cin >> cardIndex;

                if(std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cardIndex = -2;
                }

                if(0 <= cardIndex && cardIndex <= int(trashCards.size()-1) && trashCards.at(cardIndex)->isActionCard()) {
                    Card *c = b.chooseCardFromTrash(cardIndex);
                    p->getNewCard(c, true);
                    return;
                } else {
                    cardIndex = -2;
                }
            }
        }
    }
    

}

bool Lurker::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}