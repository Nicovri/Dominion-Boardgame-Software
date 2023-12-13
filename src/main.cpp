#include "game/Board.hpp"
#include "game/Player.hpp"
#include "game/Pile.hpp"
#include "game/Set.hpp"
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

#include "cards/Copper.hpp"
#include "cards/Estate.hpp"

/*
    argv[0] : program name
    argv[1] : 0 for CLI and 1 for GUI
*/
int main(int argc, char* argv[]) {
    int nbPlayers = 0;
    std::vector<Player> players;

    while(nbPlayers < 2 || nbPlayers > 4) {
        std::cout << "How many players are you? (2 to 4): ";
        std::cin >> nbPlayers;
    }

    for(int i = 1; i <= nbPlayers; i++) {
        std::string username;
        std::cout << "What is your username, player " << i << "?: ";
        std::cin >> username;
        players.push_back(Player{username});
    }

    Board b {players};

    std::vector<Card> baseDeck = {Copper(), Copper(), Copper(), Copper(), Copper(), Copper(), Copper(), Estate(), Estate(), Estate()};
    std::vector<Pile> piles = Set::getSetCards(nbPlayers, SetName::Base);

    b.initializeBoard(baseDeck, piles);

    std::cout << b << std::endl;

    b.playRound();

    std::cout << b << std::endl;

    if(argc == 2 && strcmp(argv[1], "1")) {
        
    } else {

    }

    return 0;
}