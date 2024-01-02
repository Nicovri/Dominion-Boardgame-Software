#include "Bureaucrat.hpp"
#include "../game/Board.hpp"

Bureaucrat::Bureaucrat(): Card(4, kEnumToString(KingdomCardName::Bureaucrat), true),
                    Action(4, kEnumToString(KingdomCardName::Bureaucrat), true),
                    Attack(4, kEnumToString(KingdomCardName::Bureaucrat), true) {}

/*!
//! Jouer la carte Bureaucrate: gagne un Argent sur le dessus du deck, attaque.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Bureaucrat::play(Board &b) {
    Player *cp = b.getCurrentPlayer();

    Card *c = b.chooseCard("Silver");

    if(c != NULL) {
        cp->getNewCardInDeck(c, true);
    }

    this->attack(b);
}

/*!
//! Attaquer avec la carte Bureaucrate: tous les autres joueurs révèlent une carte Victoire de leur main (s'ils en ont), et la place sur le dessus de leur deck.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Bureaucrat::attack(Board &b) {
    Player *cp = b.getCurrentPlayer();

    for(Player *p : b.getPlayers()) {
        if(p != cp) {
            bool hasReacted = useReactionToAttack(b, p);
            bool hasCounter = useCounterAttack(p);
            if((hasCounter && !hasReacted) || !hasCounter) {

                if(!p->hasVictoryCards()) {
                    return;
                }

                int cardIndex = -2;
                while(cardIndex < 0 || cardIndex > p->getNbCardsInHand()-1 ||
                        (0 <= cardIndex  && cardIndex <= p->getNbCardsInHand()-1 && !p->showCard(cardIndex)->isVictoryCard())) {

                    std::cout << p << std::endl;
                    std::cout << p->getUsername() << ", which Victory card would you like to place onto your deck?: ";
                    std::cin >> cardIndex;

                    if(std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cardIndex = -2;
                    }

                    if(0 <= cardIndex && cardIndex <= p->getNbCardsInHand()-1) {
                        Card *c = p->showCard(cardIndex);
                        if(c->isVictoryCard()) {
                            if(!p->addCardFromHandToDeck(cardIndex)) {
                                cardIndex = -2;
                            } else {
                                return;
                            }
                        }
                    }
                }

            }
        }
    }
}

bool Bureaucrat::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}