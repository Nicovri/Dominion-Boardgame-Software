#include "ThroneRoom.hpp"
#include "../game/Board.hpp"

ThroneRoom::ThroneRoom(): Card(4, kEnumToString(KingdomCardName::ThroneRoom), true),
                    Action(4, kEnumToString(KingdomCardName::ThroneRoom), true) {}

/*!
//! Jouer la carte Salle du Trône: joue une carte Action de la main 2 fois.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void ThroneRoom::play(Board &b) {
    Player *p = b.getCurrentPlayer();

    if(!p->hasActionCards()) {
        return;
    }

    int cardIndex = -2;
    while(cardIndex < -1 || cardIndex > p->getNbCardsInHand()-1 ||
            (0 <= cardIndex && cardIndex <= p->getNbCardsInHand()-1 && !p->showCard(cardIndex)->isActionCard())) {

        std::cout << p << std::endl;
        std::cout << p->getUsername() << ", which Action card would you like to play twice?: ";
        std::cin >> cardIndex;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cardIndex = -2;
        }
        if(cardIndex == -1) {
            return;
        }
        
        if(0 <= cardIndex && cardIndex <= p->getNbCardsInHand()-1 && p->showCard(cardIndex)->isActionCard()) {
            Card *c = p->showCard(cardIndex);
            bool wasDiscarded = p->discardCard(cardIndex);
            c->play(b);
            c->play(b);
            if(!wasDiscarded) {
                cardIndex = -2;
            } else {
                return;
            }
        }
        cardIndex = -2;
    }
}

bool ThroneRoom::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}