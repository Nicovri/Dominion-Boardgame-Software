#include "Set.hpp"

/*!
//! Crée une pile de carte Royaume selon le nom de la carte. Utile pour les piles de taille différente (ex - Jardins), ou pour initialiser les piles aléatoirement.
      \param cardName La valeur de l'énumération correspondant au nom de la carte Royaume.
      \return la pile de cartes créée.
*/
Pile Set::createKingdomCardPile(KingdomCardName cardName, int nbPlayers) {
    switch(cardName) {
        case KingdomCardName::Workshop: return Pile(new Workshop(), 10);
        case KingdomCardName::Woodcutter: return Pile(new Woodcutter(), 10);
        case KingdomCardName::Cellar: return Pile(new Cellar(), 10);
        case KingdomCardName::Chapel: return Pile(new Chapel(), 10);
        case KingdomCardName::Smithy: return Pile(new Smithy(), 10);
        case KingdomCardName::Market: return Pile(new Market(), 10);
        case KingdomCardName::Mine: return Pile(new Mine(), 10);
        case KingdomCardName::Remodel: return Pile(new Remodel(), 10);
        case KingdomCardName::Witch: return Pile(new Witch(), 10);
        case KingdomCardName::Village: return Pile(new Village(), 10);
        case KingdomCardName::Festival: return Pile(new Festival(), 10);
        case KingdomCardName::Laboratory: return Pile(new Laboratory(), 10);
        case KingdomCardName::Moneylender: return Pile(new Moneylender(), 10);
        case KingdomCardName::CouncilRoom: return Pile(new CouncilRoom(), 10);
        case KingdomCardName:: Gardens: return Pile(new Gardens(), nbPlayers == 2 ? 8 : 12);
        case KingdomCardName::Militia: return Pile(new Militia(), 10);
        case KingdomCardName::Poacher: return Pile(new Poacher(), 10);
        case KingdomCardName::Feast: return Pile(new Feast(), 10);
        case KingdomCardName::Bandit: return Pile(new Bandit(), 10);
        case KingdomCardName::Artisan: return Pile(new Artisan(), 10);
        case KingdomCardName::Vassal: return Pile(new Vassal(), 10);
        case KingdomCardName::Sentry: return Pile(new Sentry(), 10);
        case KingdomCardName::Chancellor: return Pile(new Chancellor(), 10);
        case KingdomCardName::Harbinger: return Pile(new Harbinger(), 10);
        case KingdomCardName::Spy: return Pile(new Spy(), 10);
        case KingdomCardName::Library: return Pile(new Library(), 10);
        case KingdomCardName::Moat: return Pile(new Moat(), 10);
        case KingdomCardName::Bureaucrat: return Pile(new Bureaucrat(), 10);
        case KingdomCardName::Merchant: return Pile(new Merchant(), 10);
        case KingdomCardName::ThroneRoom: return Pile(new ThroneRoom(), 10);
        case KingdomCardName::Adventurer: return Pile(new Adventurer(), 10);
        case KingdomCardName::Thief: return Pile(new Thief(), 10);
        case KingdomCardName::Ironworks: return Pile(new Ironworks(), 10);
        case KingdomCardName::Harem: return Pile(new Harem(), nbPlayers == 2 ? 8 : 12);
        case KingdomCardName::Replace: return Pile(new Replace(), 10);
        case KingdomCardName::Swindler: return Pile(new Swindler(), 10);
        case KingdomCardName::Mill: return Pile(new Mill(), nbPlayers == 2 ? 8 : 12);
        case KingdomCardName::MiningVillage: return Pile(new MiningVillage(), 10);
        case KingdomCardName::ShantyTown: return Pile(new ShantyTown(), 10);
        case KingdomCardName::TradingPost: return Pile(new TradingPost(), 10);
        case KingdomCardName::Steward: return Pile(new Steward(), 10);
        case KingdomCardName::Pawn: return Pile(new Pawn(), 10);
        case KingdomCardName::Lurker: return Pile(new Lurker(), 10);
        case KingdomCardName::Diplomat: return Pile(new Diplomat(), 10);
        case KingdomCardName::Courtyard: return Pile(new Courtyard(), 10);
        default: return Pile();
    }
}

/*!
//! Vérifie que tous les noms de cartes d'une liste sont uniques.
      \param cardNames la liste de noms de cartes.
      \return false si certains noms sont identiques, true si tous les noms sont uniques.
*/
bool Set::allNamesAreUniques(std::vector<KingdomCardName> cardNames) {
    std::set<KingdomCardName> uniqueNames;

    for(const auto& cardName : cardNames) {
        if(!uniqueNames.insert(cardName).second) {
            return false;
        }
    }

    return true;
}

/*!
//! Crée le deck de base d'un joueur.
      \return le deck du joueur sous forme d'une liste de cartes.
*/
std::vector<Card*> Set::getBaseDeck() {
    std::vector<Card*> baseDeck = {new Copper(), new Copper(), new Copper(), new Copper(), new Copper(), new Copper(), new Copper(), new Estate(), new Estate(), new Estate()};
    return baseDeck;
}

/*!
//! Crée une pile de cartes aléatoirement.
      \param nbPlayers le nombre de joueurs d'une partie.
      \return la liste des piles de cartes du plateau de jeu.
*/
std::vector<Pile> Set::getSetCards(int nbPlayers) {
    std::vector<Pile> randomSet;
    randomSet.push_back(Pile(new Copper(), 60 - 7*nbPlayers));
    randomSet.push_back(Pile(new Silver(), 40));
    randomSet.push_back(Pile(new Gold(), 30));
    randomSet.push_back(Pile(new Curse(), nbPlayers == 2 ? 10 : nbPlayers == 3 ? 20 : 30));
    randomSet.push_back(Pile(new Estate(), nbPlayers == 2 ? 8 : 12));
    randomSet.push_back(Pile(new Duchy(), nbPlayers == 2 ? 8 : 12));
    randomSet.push_back(Pile(new Province(), nbPlayers == 2 ? 8 : 12));

    srand(time(NULL));
    int c = 0;
    while(c < 10) {
        KingdomCardName randomCard = static_cast<KingdomCardName>(std::rand() % static_cast<int>(KingdomCardName::COUNT));
        auto it = std::find_if(randomSet.begin(), randomSet.end(),
                                [randomCard](const Pile& pile) {
                                    return pile.showCard(0)->getTitle() == kEnumToString(randomCard);
                                });
        if(it == randomSet.end()) {
            randomSet.push_back(Set::createKingdomCardPile(randomCard, nbPlayers));
            c++;
        }
    }

    return randomSet;
}

/*!
//! Crée une pile de cartes à partir d'un nom de set.
      \param nbPlayers le nombre de joueurs d'une partie.
      \param setName le nom du set choisi
      \return la liste des piles de cartes du plateau de jeu.
*/
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
        case SetName::FirstGame:
            setFromName.push_back(Pile(new Cellar(), 10));
            setFromName.push_back(Pile(new Market(), 10));
            setFromName.push_back(Pile(new Merchant(), 10));
            setFromName.push_back(Pile(new Militia(), 10));
            setFromName.push_back(Pile(new Mine(), 10));
            setFromName.push_back(Pile(new Moat(), 10));
            setFromName.push_back(Pile(new Remodel(), 10));
            setFromName.push_back(Pile(new Smithy(), 10));
            setFromName.push_back(Pile(new Village(), 10));
            setFromName.push_back(Pile(new Workshop(), 10));
            break;
        case SetName::SizeDistortion:
            setFromName.push_back(Pile(new Artisan(), 10));
            setFromName.push_back(Pile(new Bandit(), 10));
            setFromName.push_back(Pile(new Bureaucrat(), 10));
            setFromName.push_back(Pile(new Chapel(), 10));
            setFromName.push_back(Pile(new Festival(), 10));
            setFromName.push_back(Pile(new Gardens(), nbPlayers == 2 ? 8 : 12));
            setFromName.push_back(Pile(new Sentry(), 10));
            setFromName.push_back(Pile(new ThroneRoom(), 10));
            setFromName.push_back(Pile(new Witch(), 10));
            setFromName.push_back(Pile(new Workshop(), 10));
            break;
        case SetName::DeckTop:
            setFromName.push_back(Pile(new Artisan(), 10));
            setFromName.push_back(Pile(new Bureaucrat(), 10));
            setFromName.push_back(Pile(new CouncilRoom(), 10));
            setFromName.push_back(Pile(new Festival(), 10));
            setFromName.push_back(Pile(new Harbinger(), 10));
            setFromName.push_back(Pile(new Laboratory(), 10));
            setFromName.push_back(Pile(new Moneylender(), 10));
            setFromName.push_back(Pile(new Sentry(), 10));
            setFromName.push_back(Pile(new Vassal(), 10));
            setFromName.push_back(Pile(new Village(), 10));
            break;
        case SetName::SleightOfHand:
            setFromName.push_back(Pile(new Cellar(), 10));
            setFromName.push_back(Pile(new CouncilRoom(), 10));
            setFromName.push_back(Pile(new Festival(), 10));
            setFromName.push_back(Pile(new Gardens(), nbPlayers == 2 ? 8 : 12));
            setFromName.push_back(Pile(new Library(), 10));
            setFromName.push_back(Pile(new Harbinger(), 10));
            setFromName.push_back(Pile(new Militia(), 10));
            setFromName.push_back(Pile(new Poacher(), 10));
            setFromName.push_back(Pile(new Smithy(), 10));
            setFromName.push_back(Pile(new ThroneRoom(), 10));
            break;
        case SetName::Improvements:
            setFromName.push_back(Pile(new Artisan(), 10));
            setFromName.push_back(Pile(new Cellar(), 10));
            setFromName.push_back(Pile(new Market(), 10));
            setFromName.push_back(Pile(new Merchant(), 10));
            setFromName.push_back(Pile(new Mine(), 10));
            setFromName.push_back(Pile(new Moat(), 10));
            setFromName.push_back(Pile(new Moneylender(), 10));
            setFromName.push_back(Pile(new Poacher(), 10));
            setFromName.push_back(Pile(new Remodel(), 10));
            setFromName.push_back(Pile(new Witch(), 10));
            break;
        case SetName::SilverAndGold:
            setFromName.push_back(Pile(new Bandit(), 10));
            setFromName.push_back(Pile(new Bureaucrat(), 10));
            setFromName.push_back(Pile(new Chapel(), 10));
            setFromName.push_back(Pile(new Harbinger(), 10));
            setFromName.push_back(Pile(new Laboratory(), 10));
            setFromName.push_back(Pile(new Merchant(), 10));
            setFromName.push_back(Pile(new Mine(), 10));
            setFromName.push_back(Pile(new Moneylender(), 10));
            setFromName.push_back(Pile(new ThroneRoom(), 10));
            setFromName.push_back(Pile(new Vassal(), 10));
            break;
        case SetName::Deconstruction:
            setFromName.push_back(Pile(new Bandit(), 10));
            setFromName.push_back(Pile(new Mine(), 10));
            setFromName.push_back(Pile(new Remodel(), 10));
            setFromName.push_back(Pile(new ThroneRoom(), 10));
            setFromName.push_back(Pile(new Village(), 10));
            setFromName.push_back(Pile(new Diplomat(), 10));
            setFromName.push_back(Pile(new Harem(), nbPlayers == 2 ? 8 : 12));
            setFromName.push_back(Pile(new Lurker(), 10));
            setFromName.push_back(Pile(new Replace(), 10));
            setFromName.push_back(Pile(new Swindler(), 10));
            break;
        default:
            break;
    }
    return setFromName;
}

/*!
//! Crée une pile de cartes à partir de 10 noms de cartes Royaume.
      \param nbPlayers le nombre de joueurs d'une partie.
      \param cardNamei le nom de la carte choisie.
      \return la liste des piles de cartes du plateau de jeu.
*/
std::vector<Pile> Set::getSetCards(int nbPlayers,
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
        setFromCards.push_back(Set::createKingdomCardPile(cardName1, nbPlayers));
        setFromCards.push_back(Set::createKingdomCardPile(cardName2, nbPlayers));
        setFromCards.push_back(Set::createKingdomCardPile(cardName3, nbPlayers));
        setFromCards.push_back(Set::createKingdomCardPile(cardName4, nbPlayers));
        setFromCards.push_back(Set::createKingdomCardPile(cardName5, nbPlayers));
        setFromCards.push_back(Set::createKingdomCardPile(cardName6, nbPlayers));
        setFromCards.push_back(Set::createKingdomCardPile(cardName7, nbPlayers));
        setFromCards.push_back(Set::createKingdomCardPile(cardName8, nbPlayers));
        setFromCards.push_back(Set::createKingdomCardPile(cardName9, nbPlayers));
        setFromCards.push_back(Set::createKingdomCardPile(cardName10, nbPlayers));
    } else {
        return {};
    }
    
    return setFromCards;
}