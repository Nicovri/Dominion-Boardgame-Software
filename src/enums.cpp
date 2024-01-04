#include "enums.hpp"

const std::string kEnumToString(KingdomCardName value) {
    switch (value) {
        case KingdomCardName::Workshop: return "Workshop";
        case KingdomCardName::Woodcutter: return "Woodcutter";
        case KingdomCardName::Cellar: return "Cellar";
        case KingdomCardName::Chapel: return "Chapel";
        case KingdomCardName::Smithy: return "Smithy";
        case KingdomCardName::Market: return "Market";
        case KingdomCardName::Mine: return "Mine";
        case KingdomCardName::Remodel: return "Remodel";
        case KingdomCardName::Witch: return "Witch";
        case KingdomCardName::Village: return "Village";
        case KingdomCardName::Festival: return "Festival";
        case KingdomCardName::Laboratory: return "Laboratory";
        case KingdomCardName::Moneylender: return "Moneylender";
        case KingdomCardName::CouncilRoom: return "CouncilRoom";
        case KingdomCardName::Gardens: return "Gardens";
        case KingdomCardName::Militia: return "Militia";
        case KingdomCardName::Poacher: return "Poacher";
        case KingdomCardName::Feast: return "Feast";
        case KingdomCardName::Bandit: return "Bandit";
        case KingdomCardName::Artisan: return "Artisan";
        case KingdomCardName::Vassal: return "Vassal";
        case KingdomCardName::Sentry: return "Sentry";
        case KingdomCardName::Chancellor: return "Chancellor";
        case KingdomCardName::Harbinger: return "Harbinger";
        case KingdomCardName::Spy: return "Spy";
        case KingdomCardName::Library: return "Library";
        case KingdomCardName::Moat: return "Moat";
        case KingdomCardName::Bureaucrat: return "Bureaucrat";
        case KingdomCardName::Merchant: return "Merchant";
        case KingdomCardName::ThroneRoom: return "ThroneRoom";
        case KingdomCardName::Adventurer: return "Adventurer";
        case KingdomCardName::Thief: return "Thief";
        case KingdomCardName::Ironworks: return "Ironworks";
        case KingdomCardName::Harem: return "Harem";
        case KingdomCardName::Replace: return "Replace";
        case KingdomCardName::Swindler: return "Swindler";
        case KingdomCardName::Mill: return "Mill";
        case KingdomCardName::MiningVillage: return "MiningVillage";
        case KingdomCardName::ShantyTown: return "ShantyTown";
        case KingdomCardName::TradingPost: return "TradingPost";
        case KingdomCardName::Steward: return "Steward";
        case KingdomCardName::Pawn: return "Pawn";
        default: return "";
    }
}

const std::string oEnumToString(OtherCardName value) {
    switch (value) {
        case OtherCardName::Curse: return "Curse";
        case OtherCardName::Estate: return "Estate";
        case OtherCardName::Duchy: return "Duchy";
        case OtherCardName::Province: return "Province";
        case OtherCardName::Copper: return "Copper";
        case OtherCardName::Silver: return "Silver";
        case OtherCardName::Gold: return "Gold";
        default: return "";
    }
}

const std::string sEnumToString(SetName value) {
    switch (value) {
        case SetName::Base: return "Base";
        case SetName::FirstGame: return "First Game";
        case SetName::SizeDistortion: return "Size Distortion";
        case SetName::DeckTop: return "Deck Top";
        case SetName::SleightOfHand: return "Sleight of Hand";
        case SetName::Improvements: return "Improvements";
        case SetName::SilverAndGold: return "Silver & Gold";
        default: return "";
    }
}