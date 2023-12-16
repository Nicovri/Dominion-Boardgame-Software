#include "Set.hpp"

Pile Set::createActionCardPile(ActionCardName cardName) {
    switch(cardName) {
        default:
            return Pile();
    }
}

bool Set::allNamesAreUniques(std::vector<ActionCardName> cardNames) {
    std::set<ActionCardName> uniqueNames;

    for(const auto& cardName : cardNames) {
        if(!uniqueNames.insert(cardName).second) {
            return false;
        }
    }

    return true;
}

std::vector<Card*> Set::getBaseDeck() {
    std::vector<Card*> baseDeck = {new Copper(), new Copper(), new Copper(), new Copper(), new Copper(), new Copper(), new Copper(), new Estate(), new Estate(), new Estate()};
    return baseDeck;
}

std::vector<Pile> Set::getSetCards(int nbPlayers) {
    std::vector<Pile> randomSet;
    randomSet.push_back(Pile(new Copper(), 60 - 7*nbPlayers));
    randomSet.push_back(Pile(new Silver(), 40));
    randomSet.push_back(Pile(new Gold(), 30));
    randomSet.push_back(Pile(new Curse(), nbPlayers == 2 ? 10 : nbPlayers == 3 ? 20 : 30));
    randomSet.push_back(Pile(new Estate(), nbPlayers == 2 ? 8 : 12));
    randomSet.push_back(Pile(new Duchy(), nbPlayers == 2 ? 8 : 12));
    randomSet.push_back(Pile(new Province(), nbPlayers == 2 ? 8 : 12));

    // Choose 10 random action names and create the associated piles

    return randomSet;
}

std::vector<Pile> Set::getSetCards(int nbPlayers, SetName setName) {
    std::vector<Pile> setFromName;
    setFromName.push_back(Pile(new Copper(), 60 - 7*nbPlayers));
    setFromName.push_back(Pile(new Silver(), 40));
    setFromName.push_back(Pile(new Gold(), 30));
    setFromName.push_back(Pile(new Curse(), nbPlayers == 2 ? 10 : nbPlayers == 3 ? 20 : 30));
    setFromName.push_back(Pile(new Estate(), nbPlayers == 2 ? 8 : 12));
    setFromName.push_back(Pile(new Duchy(), nbPlayers == 2 ? 8 : 12));
    setFromName.push_back(Pile(new Province(), nbPlayers == 2 ? 8 : 12));
    switch(setName) {
        case SetName::Base:
            break;
        default:
            break;
    }
    return setFromName;
}

std::vector<Pile> getSetCards(int nbPlayers,
        ActionCardName cardName1, ActionCardName cardName2, ActionCardName cardName3,
        ActionCardName cardName4, ActionCardName cardName5, ActionCardName cardName6,
        ActionCardName cardName7, ActionCardName cardName8, ActionCardName cardName9,
        ActionCardName cardName10) {
    std::vector<Pile> setFromCards;
    setFromCards.push_back(Pile(new Copper(), 60 - 7*nbPlayers));
    setFromCards.push_back(Pile(new Silver(), 40));
    setFromCards.push_back(Pile(new Gold(), 30));
    setFromCards.push_back(Pile(new Curse(), nbPlayers == 2 ? 10 : nbPlayers == 3 ? 20 : 30));
    setFromCards.push_back(Pile(new Estate(), nbPlayers == 2 ? 8 : 12));
    setFromCards.push_back(Pile(new Duchy(), nbPlayers == 2 ? 8 : 12));
    setFromCards.push_back(Pile(new Province(), nbPlayers == 2 ? 8 : 12));

    std::vector<ActionCardName> cardNames = {cardName1, cardName2, cardName3, cardName4, cardName5, cardName6, cardName7, cardName8, cardName9, cardName10};

    if(Set::allNamesAreUniques(cardNames)) {
        setFromCards.push_back(Set::createActionCardPile(cardName1));
        setFromCards.push_back(Set::createActionCardPile(cardName2));
        setFromCards.push_back(Set::createActionCardPile(cardName3));
        setFromCards.push_back(Set::createActionCardPile(cardName4));
        setFromCards.push_back(Set::createActionCardPile(cardName5));
        setFromCards.push_back(Set::createActionCardPile(cardName6));
        setFromCards.push_back(Set::createActionCardPile(cardName7));
        setFromCards.push_back(Set::createActionCardPile(cardName8));
        setFromCards.push_back(Set::createActionCardPile(cardName9));
        setFromCards.push_back(Set::createActionCardPile(cardName10));
    } // Else throw error
    
    return setFromCards;
}