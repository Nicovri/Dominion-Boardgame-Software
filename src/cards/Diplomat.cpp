#include "Diplomat.hpp"
#include "../game/Board.hpp"

Diplomat::Diplomat(): Card(4, kEnumToString(KingdomCardName::Diplomat), true),
                        Action(4, kEnumToString(KingdomCardName::Diplomat), true),
                        Reaction(4, kEnumToString(KingdomCardName::Diplomat), true, 0) {}

/*!
//! Jouer la carte Diplomate: +2 cartes, si la main du joueur a 5 cartes ou moins après avoir pioché, +2 actions.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Diplomat::play(Board &b) {
    Player *p = b.getCurrentPlayer();

    p->getNewCardsFromDeck(2);

    if(p->getNbCardsInHand() <= 5) {
        p->addActions(2);
    }
}

/*!
//! Réagir avec la carte Diplomate: lorsqu'un autre joueur joue une carte Attaque, si la main contient 5 cartes ou plus, pioche 2 cartes et en défausse 3.
      \param b le plateau de jeu sur laquelle la carte est jouée.
      \param p le joueur affecté par la réaction.
*/
bool Diplomat::react(Board &b, Player *p) {
    bool hasReacted = Reaction::react(b, p);

    if(!hasReacted) {
        return !hasReacted;
    }

    std::cout << this->getTitle() << ": Counter activated." << std::endl;

    p->getNewCardsFromDeck(2);

    int cardDiscarded = 0;

    int cardIndex = -2;
    while(cardDiscarded < 3 || (cardIndex < 0 || cardIndex > p->getNbCardsInHand()-1)) {
        if(cardDiscarded == 3 || p->getNbCardsInHand() == 0) {
            return hasReacted;
        }

        std::cout << p << std::endl;
        std::cout << p->getUsername() << ", which card would you like to discard?: ";
        std::cin >> cardIndex;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cardIndex = -2;
        }

        Card *c = p->showCard(cardIndex);
        if(c != NULL) {
            if(p->discardCard(cardIndex)) {
                cardDiscarded++;
            }
        }
    }

    return hasReacted;
}

bool Diplomat::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}