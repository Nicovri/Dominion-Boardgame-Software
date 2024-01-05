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
#include "../cards/Festival.hpp"
#include "../cards/Laboratory.hpp"
#include "../cards/Moneylender.hpp"
#include "../cards/CouncilRoom.hpp"
#include "../cards/Gardens.hpp"
#include "../cards/Militia.hpp"
#include "../cards/Poacher.hpp"
#include "../cards/Feast.hpp"
#include "../cards/Bandit.hpp"
#include "../cards/Artisan.hpp"
#include "../cards/Vassal.hpp"
#include "../cards/Sentry.hpp"
#include "../cards/Chancellor.hpp"
#include "../cards/Harbinger.hpp"
#include "../cards/Spy.hpp"
#include "../cards/Library.hpp"
#include "../cards/Moat.hpp"
#include "../cards/Bureaucrat.hpp"
#include "../cards/Merchant.hpp"
#include "../cards/ThroneRoom.hpp"
#include "../cards/Adventurer.hpp"
#include "../cards/Thief.hpp"
#include "../cards/Ironworks.hpp"
#include "../cards/Harem.hpp"
#include "../cards/Replace.hpp"
#include "../cards/Swindler.hpp"
#include "../cards/Mill.hpp"
#include "../cards/MiningVillage.hpp"
#include "../cards/ShantyTown.hpp"
#include "../cards/TradingPost.hpp"
#include "../cards/Steward.hpp"
#include "../cards/Pawn.hpp"
#include "../cards/Lurker.hpp"
#include "../cards/Diplomat.hpp"
#include "../cards/Courtyard.hpp"

// Classe statique permettant l'instanciation des piles du plateau et des decks initiaux des joueurs.
class Set {
public:
    static Pile createKingdomCardPile(KingdomCardName cardName, int nbPlayers);
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