#include "Courtyard.hpp"
#include "../game/Board.hpp"

Courtyard::Courtyard(): Card(2, kEnumToString(KingdomCardName::Courtyard), true),
                        Action(2, kEnumToString(KingdomCardName::Courtyard), true) {}

/*!
//! Jouer la carte Cour: +3 cartes, place une carte de la main du joueur sur son deck.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Courtyard::play(Board &b) {
    Player *p = b.getCurrentPlayer();
    
    p->getNewCardsFromDeck(3);

    int cardIndex = -2;
    while(cardIndex < 0 || cardIndex > p->getNbCardsInHand()-1) {
        std::cout << p << std::endl;
        std::cout << p->getUsername() << ", which card would you like to put onto your deck?: ";
        std::cin >> cardIndex;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cardIndex = -2;
        }

        if(0 <= cardIndex && cardIndex <= p->getNbCardsInHand()-1) {
            if(!p->addCardFromHandToDeck(cardIndex)) {
                cardIndex = -2;
            } else {
                return;
            }
        }
    }
}

bool Courtyard::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}