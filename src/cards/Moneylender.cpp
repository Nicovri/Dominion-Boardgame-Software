#include "Moneylender.hpp"
#include "../game/Board.hpp"

Moneylender::Moneylender(): Card(4, kEnumToString(KingdomCardName::Moneylender), true),
                            Action(4, kEnumToString(KingdomCardName::Moneylender), true) {}

/*!
//! Jouer la carte Prêteur Sur Gages: écarte un Cuivre en échange de +3 pièces.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Moneylender::play(Board &b) {
    Player *p = b.getCurrentPlayer();

    bool hasCopper = false;
    for(int i = 0; i < p->getNbCardsInHand(); i++) {
        if(p->showCard(i)->getTitle() == oEnumToString(OtherCardName::Copper)) {
            hasCopper = true;
        }
    }
    if(!hasCopper) { return; }

    int cardIndex = -2;
    while(cardIndex < -1 || cardIndex > p->getNbCardsInHand()-1 ||
            (0 <= cardIndex  && cardIndex <= p->getNbCardsInHand()-1 && p->showCard(cardIndex)->getTitle() != oEnumToString(OtherCardName::Copper))) {
        if(p->getNbCardsInHand() == 0) {
            return;
        }

        std::cout << p << std::endl;
        std::cout << p->getUsername() << ", which Copper card would you like to trash (in exchange for +3 Coins)?: ";
        std::cin >> cardIndex;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cardIndex = -2;
        }

        if(cardIndex == -1) {
            return;
        }
        if(0 <= cardIndex  && cardIndex <= p->getNbCardsInHand()-1 && p->showCard(cardIndex)->getTitle() == oEnumToString(OtherCardName::Copper)) {
            if(p->trashCard(cardIndex)) {
                p->addCoins(3);
                return;
            }
        }
        cardIndex = -2;
    }
}

bool Moneylender::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}