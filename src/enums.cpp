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
        default: return "";
    }
}