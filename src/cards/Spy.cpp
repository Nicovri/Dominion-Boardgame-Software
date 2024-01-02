#include "Spy.hpp"
#include "../game/Board.hpp"

Spy::Spy(): Card(4, kEnumToString(KingdomCardName::Spy), true),
            Action(4, kEnumToString(KingdomCardName::Spy), true),
            Attack(4, kEnumToString(KingdomCardName::Spy), true) {}

/*!
//! Jouer la carte Espion: +1 carte, +1 action, attaque.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Spy::play(Board &b) {
    Player *cp = b.getCurrentPlayer();

    cp->getNewCardFromDeck();
    cp->addActions(1);

    this->attack(b);
}

/*!
//! Attaquer avec la carte Espion: chaque joueur (vous inclus) montre sa carte de dessus de deck puis la défausse ou la replace.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Spy::attack(Board &b) {
    
    for(Player *p : b.getPlayers()) {
        bool hasReacted = useReactionToAttack(b, p);
        bool hasCounter = useCounterAttack(p);
        if((hasCounter && !hasReacted) || !hasCounter) {

            Card *c = NULL;
            if(!p->showCardsInDeck(1).empty()) {
                c = p->showCardsInDeck(1).at(0);
            }
            if(c != NULL) {
                std::string choice = "";
                while(choice == "" || (choice != "Y" && choice != "N")) {
                    std::cout << p->getUsername() << ", this is your revealed card: " << c->getTitle() << ". Do you want to discard it (Y/N)?: ";
                    std::cin >> choice;
                }

                if(choice == "Y") {
                    p->addCardsFromDeckToDiscard(1);
                }
            }

        }
    }
}

bool Spy::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}