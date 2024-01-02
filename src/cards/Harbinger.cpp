#include "Harbinger.hpp"
#include "../game/Board.hpp"

Harbinger::Harbinger(): Card(3, kEnumToString(KingdomCardName::Harbinger), true),
                        Action(3, kEnumToString(KingdomCardName::Harbinger), true) {}

/*!
//! Jouer la carte Présage: +1 carte, +1 action, regarde la pile de défausse et permet de choisir une carte à placer sur le deck.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Harbinger::play(Board &b) {
    Player *p = b.getCurrentPlayer();

    p->getNewCardFromDeck();
    p->addActions(1);
    
    std::vector<Card*> discardCards = p->showCardsInDiscard(p->getNbCardsInDiscard());
    discardCards.erase(discardCards.begin());

    if(!discardCards.empty()) {
        int i = 0;
        for(Card *c : discardCards) {
            std::cout << i << ": " << c << std::endl;
            i++;
        }

        int cardIndex = -2;
        while(cardIndex < -1 || cardIndex > int(discardCards.size())-1) {

            std::cout << p->getUsername() << ", which card would you like to put onto your deck?: ";
            std::cin >> cardIndex;

            if(std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cardIndex = -2;
            }

            if(cardIndex == -1) {
                break;
            } else {
                if(!p->addCardFromDiscardToDeck(cardIndex+1)) {
                    cardIndex = -2;
                }
            }
        }
    }

}

bool Harbinger::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}