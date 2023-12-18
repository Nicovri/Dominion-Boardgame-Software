#include "game/Board.hpp"
#include "game/Player.hpp"
#include "game/Pile.hpp"
#include "game/Set.hpp"
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
// #include <SFML/Graphics.hpp>

/*
    argv[0] : program name
    argv[1] : 0 for CLI and 1 for GUI
*/
int main(int argc, char* argv[]) {
    int nbPlayers = 0;
    std::set<std::string> usedUsernames;
    std::vector<Player*> players;

    while(nbPlayers < 2 || nbPlayers > 4) {
        std::cout << "How many players are you? (2 to 4): ";
        std::cin >> nbPlayers;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            nbPlayers = 0;
        }
    }

    for(int i = 1; i <= nbPlayers; i++) {
        std::string username = "";
        bool isNewUsername = false;

        while(!isNewUsername) {
            std::cout << "What is your username, player " << i << "?: ";
            std::cin >> username;
            isNewUsername = usedUsernames.insert(username).second;
        }
        
        players.push_back(new Player{username});
    }

    Board b {players};

    std::vector<Card*> baseDeck = Set::getBaseDeck();
    std::vector<Pile> piles = Set::getSetCards(nbPlayers, SetName::Base);

    b.initializeBoard(baseDeck, piles);

    std::cout << b << std::endl;

    while(!b.gameIsOver()) {
        b.playRound();
        std::cout << b << std::endl;
    }

    b.showResults();


    if(argc == 2 && strcmp(argv[1], "1")) {
        
    } else {

    }

    return 0;
}