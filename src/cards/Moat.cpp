#include "Moat.hpp"
#include "../game/Board.hpp"

Moat::Moat(): Card(2, kEnumToString(KingdomCardName::Moat), true),
                Action(5, kEnumToString(KingdomCardName::Witch), true),
                Reaction(5, kEnumToString(KingdomCardName::Witch), true, 0) {}

/*!
//! Jouer la carte Douves: +2 cartes.
      \param b le plateau de jeu sur laquelle la carte est jouée.
*/
void Moat::play(Board &b) {
    b.getCurrentPlayer()->getNewCardsFromDeck(2);
}

/*!
//! Réagir avec la carte Douves: pas d'effet de la carte attaque jouée contre le joueur.
      \param b le plateau de jeu sur laquelle la carte est jouée.
      \param p le joueur affecté par la réaction.
*/
bool Moat::react(Board &b, Player *p) {
    bool hasReacted = Reaction::react(b, p);
    if(hasReacted) {
        std::cout << "Moat: Counter activated." << std::endl;
    }
    return hasReacted;
}

bool Moat::useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) {
    this->play(b);
    repetitiveActionCounter = repetitiveActionCounter;
    pileIndex = pileIndex;
    cardIndexInHand = cardIndexInHand;
    return true;
}