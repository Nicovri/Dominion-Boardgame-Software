#include "game/Board.hpp"
#include "game/Player.hpp"
#include "game/Pile.hpp"
#include "game/Set.hpp"
#include "components/Button.hpp"
#include "components/TextButton.hpp"
#include "components/ButtonGroup.hpp"
#include "components/TextInputField.hpp"
#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <SFML/Graphics.hpp>

/*
    argv[0] : program name
    argv[1] : 0 for CLI and 1 for GUI
*/
int main(int argc, char* argv[]) {
    int nbPlayers = 0;
    std::set<std::string> usedUsernames;
    std::vector<Player*> players;

    if(argc == 2 && strcmp(argv[1], "1") == 0) {
        //GUI
        sf::RenderWindow window(sf::VideoMode(1472, 960), "Dominion Board Game");
        window.setVerticalSyncEnabled(true);

        sf::Texture texture;
        texture.loadFromFile("assets/BaseArt.jpg");
        sf::Sprite sprite;
        sprite.setTexture(texture);

        std::map<std::string, sf::Texture> cardsTextureMap;

        sf::Font font;
        if (!font.loadFromFile("assets/open-sans.ttf")) {
            return EXIT_FAILURE;
        }

        enum GameState {
            Initial,
            UsernameInput1,
            UsernameInput2,
            UsernameInput3,
            UsernameInput4,
            Loading,
            NewBoard,
            RoundPlayer,
            Results
        };

        GameState gameState = Initial;

        bool boardGenerated = false;

        ButtonGroup selectNbPlayers;
        selectNbPlayers.addButton(2, 0.35f, 0.1f, 150.f, 50.f, "2 players", font, window);
        selectNbPlayers.addButton(3, 0.5f, 0.1f, 150.f, 50.f, "3 players", font, window);
        selectNbPlayers.addButton(4, 0.65f, 0.1f, 150.f, 50.f, "4 players", font, window);

        TextButton playButton = TextButton(0, 0.5f, 0.5f, 150.f, 50.f, "Play", font, window);
        TextButton nextButton = TextButton(0, 0.5f, 0.5f, 150.f, 50.f, "Next", font, window);

        TextInputField userInputField(0.5f, 0.3f, font, window);
        sf::Text usernameText;
        usernameText.setFont(font);
        usernameText.setFillColor(sf::Color::Black);
        int currentPlayer = 1;

        sf::Text loadingText;
        loadingText.setFont(font);
        loadingText.setFillColor(sf::Color::Black);
        loadingText.setString("Loading...");
        float xPos = 0.5f * (window.getSize().x - loadingText.getLocalBounds().width);
        float yPos = 0.4f * window.getSize().y;
        loadingText.setPosition(xPos, yPos);

        ButtonGroup pilesButtonGroup;

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                else if (event.type == sf::Event::Resized) {
                    window.setSize(sf::Vector2u(1472, 960));
                    sf::FloatRect visibleArea(0, 0, 1472, 960);
                    window.setView(sf::View(visibleArea));
                }

                else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2f mousePos = sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y));

                        if (playButton.contains(mousePos) && gameState == Initial) {
                            std::cout << "Rectangle clicked!" << std::endl;

                            nbPlayers = selectNbPlayers.getSelectedValue();
                            if (nbPlayers != -1) {
                                std::cout << "Selected Value: " << nbPlayers << std::endl;
                                usernameText.setString("What is your username, player " + std::to_string(currentPlayer) + "?: ");
                                gameState = UsernameInput1;
                            } else {
                                std::cout << "No button selected." << std::endl;
                            }
                        }

                        if(nextButton.contains(mousePos) && (gameState == UsernameInput1 || gameState == UsernameInput2 || gameState == UsernameInput3 || gameState == UsernameInput4)) {
                            std::cout << "next" << std::endl;
                            if(userInputField.getContent() != "" && usedUsernames.insert(userInputField.getContent()).second) {
                                players.push_back(new Player{userInputField.getContent()});
                                userInputField.clear();
                                currentPlayer++;
                            } else {
                                // display error message for some time?
                            }
                            usernameText.setString("What is your username, player " + std::to_string(currentPlayer) + "?: ");
                            if(currentPlayer == 2) {
                                gameState = UsernameInput2;
                            } else if(currentPlayer == 3) {
                                gameState = UsernameInput3;
                            } else if(currentPlayer == 4) {
                                gameState = UsernameInput4;
                            }
                            if(currentPlayer > nbPlayers) {
                                gameState = Loading;
                            }
                        }
                    }
                }

                else if (event.type == sf::Event::TextEntered) {
                    userInputField.handleEvent(event);
                }

                selectNbPlayers.handleEvent(event, window);
                pilesButtonGroup.handleEvent(event, window);
            }


            window.clear();
            window.draw(sprite);

            if(gameState == Initial) {
                playButton.draw(window);
                selectNbPlayers.draw(window);
            }

            if(gameState == UsernameInput1) {
                float xPos = 0.5f * (window.getSize().x - usernameText.getLocalBounds().width);
                float yPos = 0.4f * window.getSize().y;
                usernameText.setPosition(xPos, yPos);
                nextButton.draw(window);
                window.draw(usernameText);
                userInputField.draw(window);
            }

            if(gameState == UsernameInput2) {
                float xPos = 0.5f * (window.getSize().x - usernameText.getLocalBounds().width);
                float yPos = 0.4f * window.getSize().y;
                usernameText.setPosition(xPos, yPos);
                nextButton.draw(window);
                window.draw(usernameText);
                userInputField.draw(window);
            }

            if(gameState == UsernameInput3) {
                float xPos = 0.5f * (window.getSize().x - usernameText.getLocalBounds().width);
                float yPos = 0.4f * window.getSize().y;
                usernameText.setPosition(xPos, yPos);
                nextButton.draw(window);
                window.draw(usernameText);
                userInputField.draw(window);
            }

            if(gameState == UsernameInput4) {
                float xPos = 0.5f * (window.getSize().x - usernameText.getLocalBounds().width);
                float yPos = 0.4f * window.getSize().y;
                usernameText.setPosition(xPos, yPos);
                nextButton.draw(window);
                window.draw(usernameText);
                userInputField.draw(window);
            }

            if(gameState == NewBoard) {
                int t;
                if(!boardGenerated) {
                    t = 0;
                    Board b {players};
                    std::vector<Card*> baseDeck = Set::getBaseDeck();
                    std::vector<Pile> piles = Set::getSetCards(nbPlayers, SetName::Base);
                    b.initializeBoard(baseDeck, piles);
                    int i = 0;
                    float x = 0.2f;
                    float y = 0.1f;
                    for(Pile p : piles) {
                        if(!p.isEmpty()) {
                            sf::Texture cardTexture;
                            cardTexture.loadFromFile("assets/" + p.showCard(0)->getTitle() + ".jpg");
                            cardsTextureMap.insert(std::make_pair(p.showCard(0)->getTitle(), cardTexture));
                            pilesButtonGroup.addButton(i, x, y, 0.1f, cardsTextureMap.at(p.showCard(0)->getTitle()), window);
                        }
                        i++;
                        if(i % 6 == 0) { x = 0.1f; y += 0.22f; }
                        x += 0.1f;
                    }
                    boardGenerated = true;
                }
                if(t >= 300) { gameState = RoundPlayer; }
                pilesButtonGroup.draw(window);
                t++;
            }

            if(gameState == RoundPlayer) {
                playButton.setPositionRelativeToWindow(0.5f, 0.8f, window);
                pilesButtonGroup.draw(window);
                playButton.draw(window);
            }

            if(gameState == Loading) {
                window.draw(loadingText);
                gameState = NewBoard;
            }

            window.display();

        }

    } else {
        // CLI
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

        system("clear");

        while(!b.gameIsOver()) {
            std::cout << b << std::endl;
            b.playRound();
            system("clear");
        }

        b.showResults();
    }

    return 0;
}