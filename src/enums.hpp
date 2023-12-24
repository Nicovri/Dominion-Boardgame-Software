#pragma once

#include <string>

enum class KingdomCardName {
    Workshop,
    Woodcutter,
    Cellar,
    Chapel,
    Smithy,
    Market,
    Mine,
    Remodel,
    Witch,
    Village,
    COUNT
};

const std::string kEnumToString(KingdomCardName value);

enum class OtherCardName {
    Curse,
    Estate,
    Duchy,
    Province,
    Copper,
    Silver,
    Gold,
    COUNT
};

const std::string oEnumToString(OtherCardName value);

enum class SetName {
    Base, // Workshop, Woodcutter, Cellar, Chapel, Smithy, Market, Mine, Remodel, Witch, Village
    COUNT
};

const std::string sEnumToString(SetName value);