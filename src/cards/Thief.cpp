#include "Thief.hpp"
#include "../game/Board.hpp"

Thief::Thief(): Card(4, kEnumToString(KingdomCardName::Thief), true),
                    Action(4, kEnumToString(KingdomCardName::Thief), true),
                    Attack(4, kEnumToString(KingdomCardName::Thief), true) {}

/*!
//! Jouer la carte Voleur: attaque.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Thief::play(Board &b) {
    this->attack(b);
}

/*!
//! Attaquer avec la carte Voleur: tous les autres joueurs révèlent les 2 premières cartes de leur deck, écartent un Trésor que le joueur actuel choisit et a la possibilité de garder. Défausse le reste des cartes révélées.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Thief::attack(Board &b) {
    auto gain_card = [](Player *cp, Player *p, Card *c) 
    {
        if(c == NULL) {
            return;
        }

        std::string choice = "";
        while(choice == "" || (choice != "Y" && choice != "N")) {
            std::cout << cp->getUsername() << ", would you like to get this Treasure card: " << c->getTitle() << " from " << p->getUsername() << " (Y/N)?: ";
            std::cin >> choice;
        }

        if(choice == "Y") {
            Card *c = p->getTopCardFromDeck();
            if(c != NULL) {
                cp->getNewCard(c, true);
            }
        } else {
            p->trashCardsInDeck(1);
        }
    };

    Player *cp = b.getCurrentPlayer();

    for(Player *p : b.getPlayers()) {
        if(p != cp) {
            bool hasReacted = useReactionToAttack(b, p);
            bool hasCounter = useCounterAttack(p);
            if((hasCounter && !hasReacted) || !hasCounter) {

                std::vector<Card*> cardsToCheck = p->showCardsInDeck(2);
                bool mustChoose = false;

                for(Card *c : cardsToCheck) {
                    std::cout << "Shown " << c << std::endl;
                }

                if(cardsToCheck.size() == 1) {
                    if(cardsToCheck.at(0)->isTreasureCard()) {
                        gain_card(cp, p, cardsToCheck.at(0));
                    } else {
                        p->addCardsFromDeckToDiscard(1);
                    }
                }

                if(cardsToCheck.size() == 2) {
                    if(cardsToCheck.at(0)->isTreasureCard()) {
                        if(cardsToCheck.at(1)->isTreasureCard()) {
                            if(cardsToCheck.at(0)->getTitle() == cardsToCheck.at(1)->getTitle()) {
                                gain_card(cp, p, cardsToCheck.at(0));
                                p->addCardsFromDeckToDiscard(1);
                            } else {
                                mustChoose = true;
                            }
                        } else {
                            gain_card(cp, p, cardsToCheck.at(0));
                            p->addCardsFromDeckToDiscard(1);
                        }
                    } else {
                        if(cardsToCheck.at(1)->isTreasureCard()) {
                            p->addCardsFromDeckToDiscard(1);
                            gain_card(cp, p, cardsToCheck.at(1));
                        } else {
                            p->addCardsFromDeckToDiscard(2);
                        }
                    }
                }

                if(mustChoose) {
                    int cardIndex = -2;
                    while (cardIndex < 0 || cardIndex > int(cardsToCheck.size())-1)
                    {
                        int i = 0;
                        for(Card *c : cardsToCheck) {
                            std::cout << i << ": " << c << std::endl;
                            i++;
                        }
                        std::cout << cp->getUsername() << ", which Treasure card would you like to see " << p->getUsername() << " trash from those deck cards?: ";
                        std::cin >> cardIndex;

                        if(std::cin.fail()) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cardIndex = -2;
                        }

                        if(cardIndex == 0) {
                            gain_card(cp, p, cardsToCheck.at(0));
                            p->addCardsFromDeckToDiscard(1);
                        } else if(cardIndex == 1) {
                            p->addCardsFromDeckToDiscard(1);
                            gain_card(cp, p, cardsToCheck.at(1));
                        } else {
                            cardIndex = -2;
                        }
                    }
                }

            }
        }
    }
}

bool Thief::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}