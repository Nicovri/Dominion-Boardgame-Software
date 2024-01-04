#include "Replace.hpp"
#include "../game/Board.hpp"

Replace::Replace(): Card(5, kEnumToString(KingdomCardName::Replace), true),
                    Action(5, kEnumToString(KingdomCardName::Replace), true),
                    Attack(5, kEnumToString(KingdomCardName::Replace), true) {}

/*!
//! Jouer la carte Remplacement: écarte une carte de la main, fait gagner une carte coûtant jusqu'à 2 pièces de plus. Si c'est une carte Action ou Trésor, la place sur le deck. Si c'est une carte Vitcoire, attaque.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Replace::play(Board &b) {
    Player *p = b.getCurrentPlayer();
    int allowedPrice = -1;

    if(p->getNbCardsInHand() == 0) {
        return;
    }

    int cardIndex = -2;
    while(cardIndex < 0 || cardIndex > p->getNbCardsInHand()-1) {

        std::cout << p << std::endl;
        std::cout << p->getUsername() << ", which card would you like to trash (in exchange of another card costing up to 2 Coins more)?: ";
        std::cin >> cardIndex;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cardIndex = -2;
        }
    }

    if(cardIndex == -1) {
        return;
    } else {
        Card *c = p->showCard(cardIndex);
        if(c != NULL) {
            allowedPrice = c->getPrice() + 2;
            if(!p->trashCard(cardIndex)) {
                allowedPrice = -1;
            }
        }
    }
    
    Card *c = b.chooseCard(allowedPrice, true);
    if(c != NULL) {

        if(c->isActionCard() || c->isTreasureCard()) {
            p->getNewCardInDeck(c, true);
        } else {
            p->getNewCard(c, true);
        }

        if(c->isVictoryCard()) {
            this->attack(b);
        }
    }
}

/*!
//! Attaquer avec la carte Remplacement: chaque autre joueur gagne une Malédiction.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Replace::attack(Board &b) {
    Player *cp = b.getCurrentPlayer();
    
    for(Player *p : b.getPlayers()) {
        if(p != cp) {
            bool hasReacted = useReactionToAttack(b, p);
            bool hasCounter = useCounterAttack(p);
            if((hasCounter && !hasReacted) || !hasCounter) {

                Card *c = b.chooseCard("Curse");
                if(c != NULL) {
                    p->getNewCard(c, true);
                }

            }
        }
    }
}

bool Replace::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}