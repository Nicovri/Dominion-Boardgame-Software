#pragma once

#include <string>

// Enumération des noms des cartes Royaume disponibles en jeu.
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
    COUNT
};

/*!
//! Conversion de l'énumération des sets de cartes en std::string.
      \param value la valeur de l'énumération.
      \return le nom du set correspondant.
*/
const std::string sEnumToString(SetName value);