#pragma once

#include <string>

// Enumération des noms des cartes Royaume disponibles en jeu.
enum class KingdomCardName {
    // From Base

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
    Festival,
    Laboratory,
    Moneylender,
    CouncilRoom,
    Gardens,
    Militia,
    Poacher,
    Feast,
    Bandit,
    Artisan,
    Vassal,
    Sentry,
    Chancellor,
    Harbinger,
    Spy,
    Library,
    Moat,
    Bureaucrat,
    Merchant,
    ThroneRoom,
    Adventurer,
    Thief,

    // From Intrigue

    Ironworks,
    Harem,
    Replace,
    Swindler,
    Mill,
    MiningVillage,
    ShantyTown,
    TradingPost,
    Steward,
    Pawn,
    Lurker,
    Diplomat,
    Courtyard,

    COUNT
};

/*!
//! Conversion de l'énumération des cartes Royaume en std::string.
      \param value la valeur de l'énumération.
      \return le nom de la carte Royaume correspondante.
*/
const std::string kEnumToString(KingdomCardName value);

// Enumération des noms des autres cartes (Trésor et Victoire) disponibles en jeu.
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

/*!
//! Conversion de l'énumération des cartes restantes (Trésor et Victoire) en std::string.
      \param value la valeur de l'énumération.
      \return le nom de la carte correspondante.
*/
const std::string oEnumToString(OtherCardName value);

// Enumération des noms de set disponibles en jeu.
enum class SetName {
    Base, // Workshop, Woodcutter, Cellar, Chapel, Smithy, Market, Mine, Remodel, Witch, Village
    FirstGame, // Cellar, Market, Merchant, Militia, Mine, Moat, Remodel, Smithy, Village, Workshop
    SizeDistortion, // Artisan, Bandit, Bureaucrat, Chapel, Festival, Gardens, Sentry, ThroneRoom, Witch, Workshop
    DeckTop, // Artisan, Bureaucrat, CouncilRoom, Festival, Harbinger, Laboratory, Moneylender, Sentry, Vassal, Village
    SleightOfHand, // Cellar, CouncilRoom, Festival, Gardens, Library, Harbinger, Militia, Poacher, Smithy, ThroneRoom
    Improvements, // Artisan, Cellar, Market, Merchant, Mine, Moat, Moneylender, Poacher, Remodel, Witch
    SilverAndGold, // Bandit, Bureaucrat, Chapel, Harbinger, Laboratory, Merchant, Mine, Moneylender, ThroneRoom, Vassal
    Deconstruction, // Bandit, Mine, Remodel, ThroneRoom, Village, Diplomat, Harem, Lurker, Replace, Swindler
    COUNT
};

/*!
//! Conversion de l'énumération des sets de cartes en std::string.
      \param value la valeur de l'énumération.
      \return le nom du set correspondant.
*/
const std::string sEnumToString(SetName value);

// Enumération des noms des extensions disponibles en jeu.
enum class ExtensionName {
    Base,
    Intrigue,
    Seaside,

    Prosperity,

    Hinterlands,


    Adventures,
    Empires,
    Nocturne,


    Allies,
    COUNT
};

/*!
//! Conversion de l'énumération des extensions de cartes en std::string.
      \param value la valeur de l'énumération.
      \return le nom du set correspondant.
*/
const std::string eEnumToString(ExtensionName value);