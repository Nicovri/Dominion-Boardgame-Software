#include "Poacher.hpp"
#include "../game/Board.hpp"

Poacher::Poacher(): Card(4, kEnumToString(KingdomCardName::Poacher), true),
                    Action(4, kEnumToString(KingdomCardName::Poacher), true) {}

/*!
//! Jouer la carte Braconnier: +1 carte, +1 action, +1 pièce, défausse une carte pour chaque pile de jeu vide.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Poacher::play(Board &b) {
    Player *p = b.getCurrentPlayer();

    p->getNewCardFromDeck();
    p->addActions(1);
    p->addCoins(1);

    int nbEmptyPiles = b.getNbEmptyPiles();
    int nbCardsInHand = p->getNbCardsInHand();

    while(p->getNbCardsInHand() > nbCardsInHand - nbEmptyPiles) {
        int cardIndex = -2;
        std::cout << p << std::endl;
        std::cout << p->getUsername() << ", which card would you like to discard?: ";
        std::cin >> cardIndex;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cardIndex = -2;
        }
        if(!p->discardCard(cardIndex)) {
            cardIndex = -2;
        }
    }
}

bool Poacher::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}