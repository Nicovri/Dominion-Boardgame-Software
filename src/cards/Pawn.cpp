#include "Pawn.hpp"
#include "../game/Board.hpp"

Pawn::Pawn(): Card(2, kEnumToString(KingdomCardName::Pawn), true),
                Action(2, kEnumToString(KingdomCardName::Pawn), true) {}

/*!
//! Jouer la carte Pion: Choisir 2 options uniques parmi les suivantes: +1 carte, +1 action, +1 achat, +1 pièce.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Pawn::play(Board &b) {
    Player *p = b.getCurrentPlayer();

    int effectChosen1 = -1;
    int effectChosen2 = -1;

    while(effectChosen1 == effectChosen2) {
        effectChosen1 = -1;
        effectChosen2 = -1;
        
        std::cout << "\nWhat 1st effect do you want to play?\n0: +1 card\n1: +1 action\n2: +1 buy\n3: +1 coins" << std::endl;
        while(effectChosen1 < 0 || effectChosen1 > 3) {
            std::cout << "Your choice: ";
            std::cin >> effectChosen1;

            if(std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                effectChosen1 = -1;
            }
        }

        std::cout << "\nWhat 2nd effect do you want to play (different from the 1st one)?\n0: +1 card\n1: +1 action\n2: +1 buy\n3: +1 coins" << std::endl;
        while(effectChosen2 < 0 || effectChosen2 > 3) {
            std::cout << "Your choice: ";
            std::cin >> effectChosen2;

            if(std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                effectChosen2 = -1;
            }
        }
    }

    if(effectChosen1 == 0 || effectChosen2 == 0) {
        p->getNewCardFromDeck();
    }

    if(effectChosen1 == 1 || effectChosen2 == 1) {
        p->addActions(1);
    }

    if(effectChosen1 == 2 || effectChosen2 == 2) {
        p->addBuys(1);
    }

    if(effectChosen1 == 3 || effectChosen2 == 3) {
        p->addCoins(1);
    }
}

bool Pawn::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}