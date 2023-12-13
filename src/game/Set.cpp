#include "Set.hpp"

std::vector<Pile> Set::getSetCards(int nbPlayers) {
    std::vector<Pile> randomSet;
    randomSet.push_back(Pile(Copper(), 60 - 7*nbPlayers));
    randomSet.push_back(Pile(Estate(), 24 - 3*nbPlayers));
    randomSet.push_back(Pile(Duchy(), 12));
    return randomSet;
}

std::vector<Pile> Set::getSetCards(int nbPlayers, SetName setName) {
    std::vector<Pile> setFromName;
    setFromName.push_back(Pile(Copper(), 60 - 7*nbPlayers));
    setFromName.push_back(Pile(Estate(), 24 - 3*nbPlayers));
    setFromName.push_back(Pile(Duchy(), 12));
    switch(setName) {
        case SetName::Base:
            break;
        default:
            break;
    }
    return setFromName;
}

// std::vector<Pile> getSetCards(int nbPlayers,
//         ActionCardName cardName1, ActionCardName cardName2, ActionCardName cardName3,
//         ActionCardName cardName4, ActionCardName cardName5, ActionCardName cardName6,
//         ActionCardName cardName7, ActionCardName cardName8, ActionCardName cardName9,
//         ActionCardName cardName10) {
//     std::vector<Pile> setFromCards;
//     return setFromCards;
// }