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