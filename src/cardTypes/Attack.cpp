#include "Attack.hpp"
#include "../game/Board.hpp"

Attack::Attack(int price, std::string title, bool isVisible): Card(price, title, isVisible) {}

bool Attack::isActionCard() { return false; }

bool Attack::isTreasureCard() { return false; }

bool Attack::isVictoryCard() { return false; }

bool Attack::isAttackCard() { return true; }

bool Attack::isReactionCard() { return false; }

/*!
//! Exécuter la réaction des cartes si le joueur en possède et qu'elle est lancée par le fait de jouer une carte attaque.
      \param b le plateau de jeu sur laquelle la carte est jouée.
      \param p le joueur concerné.
      \return false si la réaction n'a pas été utilisée, true si elle l'a été.
*/
bool Attack::useReactionToAttack(Board &b, Player *p) {
    if(p->hasReactionCards()) {
        for(int i = 0; i < p->getNbCardsInHand(); i++) {
            if(p->showCard(i) != NULL && p->showCard(i)->isReactionCard()) {
                Reaction* r = dynamic_cast<Reaction*>(p->showCard(i));
                if(r->getConditionTriggered() == 0) {
                    return r->react(b, p);
                }
            }
        }
    }
    return false;
}

/*!
//! Le joueur possède-t-il une carte de contre dans sa main?
      \param p le joueur concerné.
      \return false si le joueur n'a pas de carte de contre, true si il en a une (de type Douves par exemple)
*/
bool Attack::useCounterAttack(Player* p) {
    if(p->hasReactionCards()) {
        for(int i = 0; i < p->getNbCardsInHand(); i++) {
            if(p->showCard(i) != NULL && p->showCard(i)->getTitle() == kEnumToString(KingdomCardName::Moat)) {
                return true;
            }
        }
    }
    return false;
}