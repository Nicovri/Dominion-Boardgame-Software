#pragma once

#include "../cardTypes/Victory.hpp"
#include "../cardTypes/Treasure.hpp"
#include "../enums.hpp"

// Classe des cartes Harem, sous-classe de Treasure et de Victory.
class Harem: public Treasure, public Victory {

public:
    Harem();
    void play(Board &b);
    void setVictoryPoints(Board &b);

    bool isTreasureCard() override { return Treasure::isTreasureCard(); }
    bool isVictoryCard() override { return Victory::isVictoryCard(); }

    bool isActionCard() override { return Treasure::isActionCard(); }
    bool isAttackCard() override { return Treasure::isAttackCard(); }
    bool isReactionCard() override { return Treasure::isReactionCard(); }
};