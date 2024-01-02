#include "Witch.hpp"
#include "../game/Board.hpp"

Witch::Witch(): Card(5, kEnumToString(KingdomCardName::Witch), true),
                Action(5, kEnumToString(KingdomCardName::Witch), true),
                Attack(5, kEnumToString(KingdomCardName::Witch), true) {}

/*!
//! Jouer la carte Sorcière: +2 cartes, attaque.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Witch::play(Board &b) {
    Player *cp = b.getCurrentPlayer();
    cp->getNewCardsFromDeck(2);
    
    this->attack(b);
}

/*!
//! Attaquer avec la carte Sorcière: chaque autre joueur gagne une Malédiction.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Witch::attack(Board &b) {
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

bool Witch::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}