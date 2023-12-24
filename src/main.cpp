#include "game/Board.hpp"
#include "game/Player.hpp"
#include "game/Pile.hpp"
#include "game/Set.hpp"
#include "game/Card.hpp"
#include "enums.hpp"
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
    int setInitOption = -1;
    std::set<std::string> usedUsernames;
    std::vector<Player*> players;
    Board b = Board();

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
        ButtonGroup cardsInHand;

        enum RoundState {
            BeginRound,
            ShowHand,
            ActionPhase,
            TreasurePhase,
            BuyPhase,
            NextPlayerTurn
        };

        RoundState roundState = BeginRound;

        TextButton chooseCardButton = TextButton(0, 0.8f, 0.5f, 150.f, 50.f, "Choose card", font, window);
        TextButton passButton = TextButton(0, 0.8f, 0.6f, 150.f, 50.f, "Pass", font, window);
        float yPosRound = 0.7f * window.getSize().y;
        sf::Text turnPlayer;
        turnPlayer.setFont(font);
        turnPlayer.setFillColor(sf::Color::Black);
        sf::Text actionText;
        actionText.setFont(font);
        actionText.setFillColor(sf::Color::Black);
        actionText.setString("Which card would you like to play?");
        float xPosRound = 0.5f * (window.getSize().x - actionText.getLocalBounds().width);
        actionText.setPosition(xPosRound, yPosRound);
        sf::Text buyText;
        buyText.setFont(font);
        buyText.setFillColor(sf::Color::Black);

        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setFillColor(sf::Color::Black);
        gameOverText.setString("Game is over! Here are the results.");
        xPosRound = 0.5f * (window.getSize().x - gameOverText.getLocalBounds().width);
        yPosRound = 0.3f * window.getSize().y;
        gameOverText.setPosition(xPosRound, yPosRound);
        sf::Text playerFinalRankText;
        playerFinalRankText.setFont(font);
        playerFinalRankText.setFillColor(sf::Color::Black);
        sf::Text wellDoneText;
        wellDoneText.setFont(font);
        wellDoneText.setFillColor(sf::Color::Black);
        wellDoneText.setString("Well done!");
        xPosRound = 0.5f * (window.getSize().x - wellDoneText.getLocalBounds().width);
        yPosRound = 0.8f * window.getSize().y;
        wellDoneText.setPosition(xPosRound, yPosRound);
        TextButton backToHomeScreenButton = TextButton(0, 0.5f, 0.9f, 400.f, 50.f, "Go back to home screen", font, window);

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

                        if(chooseCardButton.contains(mousePos)) {
                            if(roundState == ActionPhase) {
                                b.getCurrentPlayer()->playCard(cardsInHand.getSelectedValue());
                            }
                            if(roundState == BuyPhase) {
                                Card *c = b.chooseCard(b.getCurrentPlayer()->getNbCoins(), pilesButtonGroup.getSelectedValue());
                                if(c != NULL) {
                                    b.getCurrentPlayer()->getNewCard(c, false);
                                }
                            }
                        }

                        if(passButton.contains(mousePos)) {
                            if(roundState == ActionPhase) { roundState = TreasurePhase; }
                            if(roundState == BuyPhase) { roundState = NextPlayerTurn; }
                        }

                        if(backToHomeScreenButton.contains(mousePos) && gameState == Results) {
                            gameState = Initial;
                        }
                    }
                }

                else if (event.type == sf::Event::TextEntered) {
                    userInputField.handleEvent(event);
                }

                selectNbPlayers.handleEvent(event, window);
                pilesButtonGroup.handleEvent(event, window);
                cardsInHand.handleEvent(event, window);
            }


            window.clear();
            window.draw(sprite);

            if(gameState == Initial) {
                nbPlayers = 0;
                setInitOption = -1;
                usedUsernames.clear();
                players.clear();
                b.getPlayers().clear();
                b = Board();
                boardGenerated = false;
                currentPlayer = 1;
                roundState = BeginRound;
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
                    b = Board(players);
                    std::vector<Card*> baseDeck = Set::getBaseDeck();
                    std::vector<Pile> piles = Set::getSetCards(nbPlayers, SetName::Base);
                    b.initializeBoard(baseDeck, piles);
                    int i = 0;
                    float x = 0.05f;
                    float y = 0.05f;
                    for(Pile p : piles) {
                        if(!p.isEmpty()) {
                            sf::Texture cardTexture;
                            cardTexture.loadFromFile("assets/" + p.showCard(0)->getTitle() + ".jpg");
                            cardsTextureMap.insert(std::make_pair(p.showCard(0)->getTitle(), cardTexture));
                            pilesButtonGroup.addButton(i, x, y, 0.1f, cardsTextureMap.at(p.showCard(0)->getTitle()), window);
                        }
                        i++;
                        x += 0.1f;
                        if(i % 6 == 0) { x = 0.05f; y += 0.22f; }
                    }
                    boardGenerated = true;
                }
                if(t >= 100) { gameState = RoundPlayer; }
                pilesButtonGroup.draw(window);
                t++;
            }

            if(gameState == RoundPlayer) {
                if(b.gameIsOver()) {
                    gameState = Results;
                }

                int tp;

                Player* p = b.getCurrentPlayer();

                turnPlayer.setString("Current player: " + p->getUsername() +
                                    "\nNb Actions: " + std::to_string(p->getNbActions()) +
                                    "\nNb Buys: " + std::to_string(p->getNbBuys()) +
                                    "\nNb Coins: " + std::to_string(p->getNbCoins()) +
                                    "\nNb Victory: " + std::to_string(p->getTotalVictoryPoints()));
                float yPosRoundName = 0.2f * window.getSize().y;
                xPosRound = 0.85f * (window.getSize().x - turnPlayer.getLocalBounds().width);
                turnPlayer.setPosition(xPosRound, yPosRoundName);

                float x = 0.05f;
                for(int i = 0; i < p->getNbCardsInHand(); i++) {
                    cardsInHand.addButton(i, x, 0.75f, 0.1f, cardsTextureMap.at(p->showCard(i)->getTitle()), window);
                    x += 0.1f;
                }

                // Same problem here, when pile is empty, it is still drawn
                pilesButtonGroup.draw(window);
                window.draw(turnPlayer);
                // Hand card discarded are still visible and when cards move they don't change place but redraw.
                cardsInHand.draw(window);

                if(roundState == BeginRound) {
                    p->beginRound();
                    tp = 0;
                    roundState = ShowHand;
                }

                if(roundState == ShowHand) {
                    tp++;
                    if(tp >= 30) {
                        roundState = ActionPhase;
                    }
                }
                
                if(tp >= 30) {
                    chooseCardButton.draw(window);
                    passButton.draw(window);
                }

                if(roundState == ActionPhase) {
                    if(p->hasActionCards() && p->getNbActions() > 0) {
                        window.draw(actionText);
                    } else {
                        roundState = TreasurePhase;
                    }
                }

                if(roundState == TreasurePhase) {
                    if(!p->hasTreasureCards()) {
                        roundState = BuyPhase;
                    }

                    std::vector<int> treasuresInHand = {};
                    for(int i = p->getNbCardsInHand()-1; i >= 0; i--) {
                        if(p->showCard(i)->isTreasureCard()) {
                            treasuresInHand.push_back(i);
                        }
                    }
                    for(int i : treasuresInHand) {
                        p->playCard(i);
                        cardsInHand.removeButton(i);
                        cardsInHand.draw(window);
                    }
                    roundState = BuyPhase;
                }

                if(roundState == BuyPhase) {
                    if(p->getNbBuys() <= 0) {
                        roundState = NextPlayerTurn;
                    }

                    buyText.setString("Which card would you like to buy (you currently have " + std::to_string(p->getNbCoins()) + " coins)?");
                    float yPosRoundMessage = 0.7f * window.getSize().y;
                    xPosRound = 0.5f * (window.getSize().x - buyText.getLocalBounds().width);
                    buyText.setPosition(xPosRound, yPosRoundMessage);
                    window.draw(buyText);
                }

                if(roundState == NextPlayerTurn) {
                    p->finishRound();
                    b.nextPlayerRound();
                    cardsInHand.clear();
                    roundState = BeginRound;
                }
            }

            if(gameState == Results) {
                players = b.getPlayers();
                std::sort(players.begin(), players.end(), [](const Player* l, const Player* r) {
                    return l->getTotalVictoryPoints() < r->getTotalVictoryPoints();
                });
                for(int i = 1; i <= int(b.getPlayers().size()); i++) {
                    playerFinalRankText.setString(std::to_string(i) + ": " + b.getPlayers().at(i-1)->getUsername() + " with " + std::to_string(b.getPlayers().at(i-1)->getTotalVictoryPoints()) + " VP");
                    float x = 0.5f * (window.getSize().x - playerFinalRankText.getLocalBounds().width);
                    float y = 0.1 * (i + 3) * window.getSize().y;
                    playerFinalRankText.setPosition(x, y);
                    window.draw(playerFinalRankText);
                }
                window.draw(gameOverText);
                window.draw(wellDoneText);
                backToHomeScreenButton.draw(window);
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

        b = Board(players);

        std::cout << "\nHow do you want to choose Kingdom cards?\n0: Randomly\n1: Set Name\n2: Each Card Name" << std::endl;
        while(setInitOption < 0 || setInitOption > 2) {
            std::cout << "Your choice: ";
            std::cin >> setInitOption;
        }

        std::vector<Card*> baseDeck = Set::getBaseDeck();
        std::vector<Pile> piles = {};

        if(setInitOption == 0) { piles = Set::getSetCards(nbPlayers); }
        if(setInitOption == 1) {
            setInitOption = -1;
            while(setInitOption < 0 || setInitOption > static_cast<int>(SetName::COUNT)-1) {
                for(int i = 0; i < static_cast<int>(SetName::COUNT); i++) {
                    std::cout << i << ": " << sEnumToString(static_cast<SetName>(i)) << std::endl;
                }
                std::cout << std::endl;
                std::cout << "Which Set would you like to use?: ";
                std::cin >> setInitOption;
            }
            piles = Set::getSetCards(nbPlayers, static_cast<SetName>(setInitOption));
        }
        if(setInitOption == 2) {
            while(piles.empty()) {
                std::vector<KingdomCardName> chosenCards = {};
                for(int i = 0; i < 10; i++) {
                    setInitOption = -1;
                    while(setInitOption < 0 || setInitOption > static_cast<int>(KingdomCardName::COUNT)-1) {
                        for(int i = 0; i < static_cast<int>(KingdomCardName::COUNT); i++) {
                            std::cout << i << ": " << kEnumToString(static_cast<KingdomCardName>(i)) << std::endl;
                        }
                        std::cout << std::endl;
                        std::cout << "Which Kingdom Card " << i+1 << " would you like to use?: ";
                        std::cin >> setInitOption;
                    }
                    chosenCards.push_back(static_cast<KingdomCardName>(setInitOption));
                }
                piles = Set::getSetCards(nbPlayers, chosenCards.at(0), chosenCards.at(1), chosenCards.at(2),
                                        chosenCards.at(3), chosenCards.at(4), chosenCards.at(5),
                                        chosenCards.at(6), chosenCards.at(7), chosenCards.at(8), chosenCards.at(9));
                if(piles.empty()) {
                    std::cout << "You must only choose different cards... Please make your choice again." << std::endl;
                }
            }
        }

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