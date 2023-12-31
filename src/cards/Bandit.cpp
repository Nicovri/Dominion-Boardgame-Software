#include "Bandit.hpp"
#include "../game/Board.hpp"

Bandit::Bandit(): Action(5, kEnumToString(KingdomCardName::Bandit), true) {}

/*!
//! Jouer la carte Brigant: gagne un Or, tous les autres joueurs révèlent les 2 premières cartes de leur deck, écartent un Trèsor autre que Cuivre et défaussent le reste.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Bandit::play(Board &b) {
    Player *cp = b.getCurrentPlayer();

    Card *c = b.chooseCard("Gold");

    if(c != NULL) {
        cp->getNewCard(c, true);
    }

    for(Player *p : b.getPlayers()) {
        if(p != cp) {
            std::vector<Card*> cardsToCheck = p->showCardsInDeck(2);
            bool mustChoose = false;

            for(Card *c : cardsToCheck) {
                std::cout << "Shown " << c << std::endl;
            }

            if(cardsToCheck.size() == 1) {
                if(cardsToCheck.at(0)->isTreasureCard() && cardsToCheck.at(0)->getTitle() != oEnumToString(OtherCardName::Copper)) {
                    p->trashCardsInDeck(1);
                } else {
                    p->addCardsFromDeckToDiscard(1);
                }
            }

            if(cardsToCheck.size() == 2) {
                if(cardsToCheck.at(0)->isTreasureCard() && cardsToCheck.at(0)->getTitle() != oEnumToString(OtherCardName::Copper)) {
                    if(cardsToCheck.at(1)->isTreasureCard() && cardsToCheck.at(1)->getTitle() != oEnumToString(OtherCardName::Copper)) {
                        if(cardsToCheck.at(0)->getTitle() == cardsToCheck.at(1)->getTitle()) {
                            p->trashCardsInDeck(1);
                            p->addCardsFromDeckToDiscard(1);
                        } else {
                            mustChoose = true;
                        }
                    } else {
                        p->trashCardsInDeck(1);
                        p->addCardsFromDeckToDiscard(1);
                    }
                } else {
                    if(cardsToCheck.at(1)->isTreasureCard() && cardsToCheck.at(1)->getTitle() != oEnumToString(OtherCardName::Copper)) {
                        p->addCardsFromDeckToDiscard(1);
                        p->trashCardsInDeck(1);
                    } else {
                        p->addCardsFromDeckToDiscard(2);
                    }
                }
            }

            if(mustChoose) {
                int cardIndex = -2;
                while (cardIndex < 0 || cardIndex > int(cardsToCheck.size())-1)
                {
                    int i = 0;
                    for(Card *c : cardsToCheck) {
                        std::cout << i << ": " << c << std::endl;
                        i++;
                    }
                    std::cout << p->getUsername() << ", which Treasure card other than Copper would you like to trash from those deck cards?: ";
                    std::cin >> cardIndex;

                    if(std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cardIndex = -2;
                    }

                    if(cardIndex == 0) {
                        p->trashCardsInDeck(1);
                        p->addCardsFromDeckToDiscard(1);
                    } else if(cardIndex == 1) {
                        p->addCardsFromDeckToDiscard(1);
                        p->trashCardsInDeck(1);
                    } else {
                        cardIndex = -2;
                    }
                }
            }
        }
    }
}

bool Bandit::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}