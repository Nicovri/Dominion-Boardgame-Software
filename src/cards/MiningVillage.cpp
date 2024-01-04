#include "MiningVillage.hpp"
#include "../game/Board.hpp"

MiningVillage::MiningVillage(): Card(4, kEnumToString(KingdomCardName::MiningVillage), true),
                                Action(4, kEnumToString(KingdomCardName::MiningVillage), true) {}

/*!
//! Jouer la carte Village Minier: +1 carte, +2 actions, peut permettre d'écarter cette carte pour +2 pièces.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void MiningVillage::play(Board &b) {
    Player *p = b.getCurrentPlayer();

    // TODO ici aussi, une pile des cartes jouées à ce tour par le joueur serait nécessaire pour éviter ce genre de workaround
    // Pour éviter de mélanger les cartes de la défausse et perdre cette carte si jamais le deck est vide (action effectuée juste après avoir écarté cette carte dans ce cas)
    bool gotNewCard = false;
    if(p->getNbCardsInDeck() > 0) {
        p->getNewCardFromDeck();
        gotNewCard = true;
    }
    p->addActions(2);

    std::string choice = "";
    while(choice == "" || (choice != "Y" && choice != "N")) {

        std::cout << p << std::endl;
        std::cout << p->getUsername() << ", would you like to trash this played card: " << this->getTitle() << " in exchange of +2 coins (Y/N)?: ";
        std::cin >> choice;
    }

    if(choice == "Y") {
        p->trashCardsInDiscard(1);
        p->addCoins(2);
    }

    if(!gotNewCard) {
        p->getNewCardFromDeck();
    }
}

bool MiningVillage::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}