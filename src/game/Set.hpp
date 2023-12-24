#pragma once

#include <vector>
#include <set>
#include <cstdlib>
#include "Pile.hpp"
#include "../cardTypes/Action.hpp"
#include "../enums.hpp"
#include "../cards/Copper.hpp"
#include "../cards/Silver.hpp"
#include "../cards/Gold.hpp"
#include "../cards/Curse.hpp"
#include "../cards/Estate.hpp"
#include "../cards/Duchy.hpp"
#include "../cards/Province.hpp"
#include "../cards/Workshop.hpp"
#include "../cards/Woodcutter.hpp"
#include "../cards/Cellar.hpp"
#include "../cards/Chapel.hpp"
#include "../cards/Smithy.hpp"
#include "../cards/Market.hpp"
#include "../cards/Mine.hpp"
#include "../cards/Remodel.hpp"
#include "../cards/Witch.hpp"
#include "../cards/Village.hpp"

class Set {
public:
    static Pile createKingdomCardPile(KingdomCardName cardName);
    static bool allNamesAreUniques(std::vector<KingdomCardName> cardNames);
    static std::vector<Card*> getBaseDeck();
    static std::vector<Pile> getSetCards(int nbPlayers);
    static std::vector<Pile> getSetCards(int nbPlayers, SetName setName);
    static std::vector<Pile> getSetCards(int nbPlayers,
        KingdomCardName cardName1, KingdomCardName cardName2, KingdomCardName cardName3,
        KingdomCardName cardName4, KingdomCardName cardName5, KingdomCardName cardName6,
        KingdomCardName cardName7, KingdomCardName cardName8, KingdomCardName cardName9,
        KingdomCardName cardName10);
};