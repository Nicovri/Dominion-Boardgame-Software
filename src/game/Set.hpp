#pragma once

#include <vector>
#include <set>
#include "Pile.hpp"
#include "../cardTypes/Action.hpp"
#include "../enums.cpp"
#include "../cards/Copper.hpp"
#include "../cards/Silver.hpp"
#include "../cards/Gold.hpp"
#include "../cards/Curse.hpp"
#include "../cards/Estate.hpp"
#include "../cards/Duchy.hpp"
#include "../cards/Province.hpp"

class Set {
public:
    static Pile createActionCardPile(ActionCardName cardName);
    static bool allNamesAreUniques(std::vector<ActionCardName> cardNames);
    static std::vector<Card*> getBaseDeck();
    static std::vector<Pile> getSetCards(int nbPlayers);
    static std::vector<Pile> getSetCards(int nbPlayers, SetName setName);
    static std::vector<Pile> getSetCards(int nbPlayers,
        ActionCardName cardName1, ActionCardName cardName2, ActionCardName cardName3,
        ActionCardName cardName4, ActionCardName cardName5, ActionCardName cardName6,
        ActionCardName cardName7, ActionCardName cardName8, ActionCardName cardName9,
        ActionCardName cardName10);
};