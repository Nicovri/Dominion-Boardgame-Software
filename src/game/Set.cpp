#include "Set.hpp"

Pile Set::createKingdomCardPile(KingdomCardName cardName) {
    switch(cardName) {
        case KingdomCardName::Workshop:
            return Pile(new Workshop(), 10);
            break;
        case KingdomCardName::Woodcutter:
            return Pile(new Woodcutter(), 10);
            break;
        case KingdomCardName::Cellar:
            return Pile(new Cellar(), 10);
            break;
        case KingdomCardName::Chapel:
            return Pile(new Chapel(), 10);
            break;
        case KingdomCardName::Smithy:
            return Pile(new Smithy(), 10);
            break;
        case KingdomCardName::Market:
            return Pile(new Market(), 10);
            break;
        case KingdomCardName::Mine:
            return Pile(new Mine(), 10);
            break;
        case KingdomCardName::Remodel:
            return Pile(new Remodel(), 10);
            break;
        case KingdomCardName::Witch:
            return Pile(new Witch(), 10);
            break;
        case KingdomCardName::Village:
            return Pile(new Village(), 10);
            break;
        default:
            return Pile();
            break;
    }
}

bool Set::allNamesAreUniques(std::vector<KingdomCardName> cardNames) {
    std::set<KingdomCardName> uniqueNames;

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
            setFromName.push_back(Pile(new Workshop(), 10));
            setFromName.push_back(Pile(new Woodcutter(), 10));
            setFromName.push_back(Pile(new Cellar(), 10));
            setFromName.push_back(Pile(new Chapel(), 10));
            setFromName.push_back(Pile(new Smithy(), 10));
            setFromName.push_back(Pile(new Market(), 10));
            setFromName.push_back(Pile(new Mine(), 10));
            setFromName.push_back(Pile(new Remodel(), 10));
            setFromName.push_back(Pile(new Witch(), 10));
            setFromName.push_back(Pile(new Village(), 10));
            break;
        default:
            break;
    }
    return setFromName;
}

std::vector<Pile> getSetCards(int nbPlayers,
        KingdomCardName cardName1, KingdomCardName cardName2, KingdomCardName cardName3,
        KingdomCardName cardName4, KingdomCardName cardName5, KingdomCardName cardName6,
        KingdomCardName cardName7, KingdomCardName cardName8, KingdomCardName cardName9,
        KingdomCardName cardName10) {
    std::vector<Pile> setFromCards;
    setFromCards.push_back(Pile(new Copper(), 60 - 7*nbPlayers));
    setFromCards.push_back(Pile(new Silver(), 40));
    setFromCards.push_back(Pile(new Gold(), 30));
    setFromCards.push_back(Pile(new Curse(), nbPlayers == 2 ? 10 : nbPlayers == 3 ? 20 : 30));
    setFromCards.push_back(Pile(new Estate(), nbPlayers == 2 ? 8 : 12));
    setFromCards.push_back(Pile(new Duchy(), nbPlayers == 2 ? 8 : 12));
    setFromCards.push_back(Pile(new Province(), nbPlayers == 2 ? 8 : 12));

    std::vector<KingdomCardName> cardNames = {cardName1, cardName2, cardName3, cardName4, cardName5, cardName6, cardName7, cardName8, cardName9, cardName10};

    if(Set::allNamesAreUniques(cardNames)) {
        setFromCards.push_back(Set::createKingdomCardPile(cardName1));
        setFromCards.push_back(Set::createKingdomCardPile(cardName2));
        setFromCards.push_back(Set::createKingdomCardPile(cardName3));
        setFromCards.push_back(Set::createKingdomCardPile(cardName4));
        setFromCards.push_back(Set::createKingdomCardPile(cardName5));
        setFromCards.push_back(Set::createKingdomCardPile(cardName6));
        setFromCards.push_back(Set::createKingdomCardPile(cardName7));
        setFromCards.push_back(Set::createKingdomCardPile(cardName8));
        setFromCards.push_back(Set::createKingdomCardPile(cardName9));
        setFromCards.push_back(Set::createKingdomCardPile(cardName10));
    } // Else throw error
    
    return setFromCards;
}