#include "Militia.hpp"
#include "../game/Board.hpp"

Militia::Militia(): Card(4, kEnumToString(KingdomCardName::Militia), true),
                    Action(4, kEnumToString(KingdomCardName::Militia), true),
                    Attack(4, kEnumToString(KingdomCardName::Militia), true) {}

/*!
//! Jouer la carte Milice: +2 pièces, attaque.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Militia::play(Board &b) {
    Player *cp = b.getCurrentPlayer();
    
    cp->addCoins(2);

    this->attack(b);
}

/*!
//! Attaquer avec la carte Milice: tous les autres joueurs défaussent jusqu'à avoir 3 cartes en main.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Militia::attack(Board &b) {
    Player *cp = b.getCurrentPlayer();
    
    for(Player *p : b.getPlayers()) {
        if(p != cp) {
            bool hasReacted = useReactionToAttack(b, p);
            bool hasCounter = useCounterAttack(p);
            if((hasCounter && !hasReacted) || !hasCounter) {

                while(p->getNbCardsInHand() > 3) {
                    int cardIndex = -2;
                    std::cout << p << std::endl;
                    std::cout << p->getUsername() << ", which card would you like to discard from your hand (down to 3 cards)?: ";
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
        }
    }
}

bool Militia::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}