#include "Swindler.hpp"
#include "../game/Board.hpp"

Swindler::Swindler(): Card(3, kEnumToString(KingdomCardName::Swindler), true),
                    Action(3, kEnumToString(KingdomCardName::Swindler), true),
                    Attack(3, kEnumToString(KingdomCardName::Swindler), true) {}

/*!
//! Jouer la carte Escroc: +2 pièces, attaque.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Swindler::play(Board &b) {
    b.getCurrentPlayer()->addCoins(2);

    this->attack(b);
}

/*!
//! Attaquer avec la carte Escroc: pour chaque autre joueur, écarte la carte du dessus du deck, gagne une carte de la même valeur que le joueur actuel choisit.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Swindler::attack(Board &b) {
    Player *cp = b.getCurrentPlayer();
    
    for(Player *p : b.getPlayers()) {
        if(p != cp) {
            bool hasReacted = useReactionToAttack(b, p);
            bool hasCounter = useCounterAttack(p);
            if((hasCounter && !hasReacted) || !hasCounter) {

                int allowedPrice = -1;
                std::vector<Card*> card = p->showCardsInDeck(1);
                if(card.empty()) {
                    return;
                }

                allowedPrice = card.at(0)->getPrice();
                p->trashCardsInDeck(1);

                int canGetCardSamePrice = false;
                for(Pile pile : b.getPiles()) {
                    if(!pile.isEmpty() && pile.showCard(0)->getPrice() == allowedPrice) {
                        canGetCardSamePrice = true;
                    }
                }
                if(!canGetCardSamePrice) {
                    return;
                }

                int pileIndex = -2;
                b.displayFilteredPiles([allowedPrice](const Pile p) { return !p.isEmpty() && p.showCard(0)->getPrice() == allowedPrice; });
                while(pileIndex < 0 || pileIndex > b.getNbPiles()-1 ||
                    (0 <= pileIndex  && pileIndex <= b.getNbPiles()-1 && (b.getPiles().at(pileIndex).isEmpty() || b.getPiles().at(pileIndex).showCard(0)->getPrice() > allowedPrice))) {
                    std::cout << cp->getUsername() << ", which card would you like to give to " << p->getUsername() << " (costing exactly " << allowedPrice << " coins)?: ";
                    std::cin >> pileIndex;

                    if(std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        pileIndex = -2;
                    }
                }
                Card *c = b.chooseCard(allowedPrice, pileIndex);
                if(c != NULL) {
                    p->getNewCard(c, true);
                }

            }
        }
    }
}

bool Swindler::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}