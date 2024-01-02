#pragma once

#include "../game/Card.hpp"
#include <string>

// Classe des cartes Action, sous-classe de Card.
class Action: public virtual Card {
    std::string effectText;

public:
    Action(int price, std::string title, bool isVisible);
    Action(int price, std::string title, bool isVisible, std::string effectText);
    virtual ~Action() = default;
    std::string getEffectText() const;
    bool isActionCard();
    bool isTreasureCard();
    bool isVictoryCard();
    bool isAttackCard();
    bool isReactionCard();
    virtual void play(Board &b) = 0;
    
    /*!
    //! Jouer la carte directement dans l'interface graphique (NE FONCTIONNE PAS ENCORE).
        \return false si la carte n'a pas pu être jouée, true si la carte a été jouée.
    */
    virtual bool useEffect(Board &b, int repetitiveActionCounter, int pileIndex, int cardIndexInHand) = 0;
};