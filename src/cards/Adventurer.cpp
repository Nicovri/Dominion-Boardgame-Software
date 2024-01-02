#include "Adventurer.hpp"
#include "../game/Board.hpp"

Adventurer::Adventurer(): Card(6, kEnumToString(KingdomCardName::Adventurer), true),
                    Action(6, kEnumToString(KingdomCardName::Adventurer), true) {}

/*!
//! Jouer la carte Aventurier: pioche et révèle les cartes du deck jusqu'à avoir 2 cartes Trésor, place ces 2 cartes Trésor dans la main et défausse les autres cartes.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Adventurer::play(Board &b) {
    Player *p = b.getCurrentPlayer();

    int treasureShown = 0;
    
    std::vector<Card*> cardsToDiscardAfterwards = {};

    while(treasureShown < 2 || (p->getNbCardsInDeck() == 0 && p->getNbCardsInDiscard() == 0)) {
        if(treasureShown == 2) {
            break;
        }

        p->getNewCardFromDeck();

        std::cout << "Shown " << p->showCard(p->getNbCardsInHand()-1) << std::endl;

        if(!p->showCard(p->getNbCardsInHand()-1)->isTreasureCard()) {
            Card *c = p->getCardFromHand(p->getNbCardsInHand()-1);
            if(c != NULL) {
                cardsToDiscardAfterwards.push_back(c);
            }
        } else {
            treasureShown++;
        }
    }

    for(Card *c : cardsToDiscardAfterwards) {
        p->getNewCard(c, true);
    }
}

bool Adventurer::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}