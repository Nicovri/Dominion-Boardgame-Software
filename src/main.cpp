#include "game/Board.hpp"
#include "game/Player.hpp"
#include "game/Pile.hpp"
#include "game/Set.hpp"
#include "game/Card.hpp"
#include "enums.hpp"
#include "components/Button.hpp"
#include "components/TextButton.hpp"
#include "components/ImageButton.hpp"
#include "components/ButtonGroup.hpp"
#include "components/TextInputField.hpp"
#include <iostream>
#include <cstring>
#include <cmath>
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
    std::vector<KingdomCardName> chosenCards = {};
    std::set<std::string> usedUsernames;
    std::vector<Player*> players;
    std::vector<Pile> piles;
    Board b = Board();
    Board bSave = Board();

    if(argc == 2 && strcmp(argv[1], "1") == 0) {
        //GUI

        // Fenêtre de jeu
        sf::RenderWindow window(sf::VideoMode(1856, 1024), "Dominion Board Game");
        window.setVerticalSyncEnabled(true);

        // Variables de style
        const sf::Color TEXT_COLOR = sf::Color::Black;
        sf::FloatRect textPositionToCenter;
        float xPos;
        float yPos;
        sf::Font font;
        if (!font.loadFromFile("assets/open-sans.ttf")) { return EXIT_FAILURE; }
        const float X_PILES_BOARD = 0.02f;
        const float Y_PILES_BOARD = 0.02f;
        const float X_OFFSET_CARD = 0.08f;
        const float Y_OFFSET_CARD = 0.21f;
        const float X_OFFSET_LABEL_TD = 0.033f; // label rebut et défausse
        const float X_OFFSET_LABEL_D = 0.034f; // label deck
        const float Y_OFFSET_LABEL = 0.021f;
        const float X_PLAY_TEXT = 0.52f;
        const float Y_PLAY_TEXT = 0.7f;
        const float X_PLAYER_INFO = 0.75f;

        // Texture de fond d'écran
        sf::Texture texture;
        texture.loadFromFile("assets/BaseArt.jpg");
        sf::Sprite sprite;
        sprite.setTexture(texture);

        // Texture d'arrière des cartes
        sf::Texture CardBackTexture;
        CardBackTexture.loadFromFile("assets/Card_back.jpg");
        sf::Sprite backSprite;
        backSprite.setTexture(CardBackTexture);

        // Map de toutes les textures de cartes utilisées lors d'une partie
        std::map<std::string, sf::Texture> cardsTextureMap;

        // Différents états de jeu. Traduisent l'apparence en cours de l'interface.
        enum GameState {
            Initial,
            Resume,
            UsernameInput,
            SetGeneration,
            Loading,
            NewBoard,
            RoundPlayer,
            CardDetails,
            Results
        };

        GameState gameState = Initial;

        bool boardGenerated = false;

        // Le groupe de bouton de sélection du nombre de joueurs.
        ButtonGroup selectNbPlayers;
        selectNbPlayers.addButton(2, 0.35f, 0.3f, 150.f, 50.f, "2 Players", font, 24, window);
        selectNbPlayers.addButton(3, 0.5f, 0.3f, 150.f, 50.f, "3 Players", font, 24, window);
        selectNbPlayers.addButton(4, 0.65f, 0.3f, 150.f, 50.f, "4 Players", font, 24, window);

        // Le groupe de bouton du choix de sélection des 10 cartes Royaume.
        ButtonGroup selectSetInitMode;
        selectSetInitMode.addButton(0, 0.3f, 0.4f, 200.f, 50.f, "Random Set", font, 24, window);
        selectSetInitMode.addButton(1, 0.5f, 0.4f, 200.f, 50.f, "Predefined Set", font, 24, window);
        selectSetInitMode.addButton(2, 0.7f, 0.4f, 200.f, 50.f, "Choose 10 Cards", font, 24, window);

        // Text invitant au choix des options.
        sf::Text chooseOptionsText;
        chooseOptionsText.setFont(font);
        chooseOptionsText.setFillColor(TEXT_COLOR);
        chooseOptionsText.setString("Please choose desired options before starting the game.");
        textPositionToCenter = chooseOptionsText.getLocalBounds();
        chooseOptionsText.setOrigin(textPositionToCenter.width/2, textPositionToCenter.height/2);
        xPos = 0.5f * window.getSize().x;
        yPos = 0.5f * window.getSize().y;
        chooseOptionsText.setPosition(xPos, yPos);

        // Boutons jouer, reprendre la partie et suivant (pour le choix des noms des joueurs et du set de 10 cartes).
        TextButton playButton = TextButton(0, 0.5f, 0.7f, 150.f, 50.f, "Play", font, 24, window);
        TextButton resumeButton = TextButton(0, 0.5f, 0.8f, 150.f, 50.f, "Resume", font, 24, window);
        TextButton nextButton = TextButton(0, 0.5f, 0.7f, 150.f, 50.f, "Next", font, 24, window);

        // Champ de saisie du nom des joueurs.
        TextInputField userInputField(0.5f, 0.4f, font, window);
        sf::Text usernameText;
        usernameText.setFont(font);
        usernameText.setFillColor(TEXT_COLOR);
        int currentPlayer = 1;

        // Le groupe de boutons qui contient tous les sets disponibles au choix.
        ButtonGroup selectSetName;
        float xS = 0.1f;
        float yS = 0.1f;
        for(int i = 0; i < static_cast<int>(SetName::COUNT); i++) {
            selectSetName.addButton(i, xS, yS, 200.f, 50.f, sEnumToString(static_cast<SetName>(i)), font, 24, window);
            xS += 0.18f;
            if((i+1) % 5 == 0 && i != 0) { xS = 0.1f; yS += 0.1f; }
        }
        // Le groupe de boutons qui contient toutes les cartes Royaume disponibles au choix.
        ButtonGroup selectCardNames;
        // Le texte qui va récapituler les cartes déjà choisies.
        sf::Text cardName;
        cardName.setFont(font);
        cardName.setFillColor(TEXT_COLOR);
        int cardChosen = 0;

        // Texte de l'écran de chargement.
        sf::Text loadingText;
        loadingText.setFont(font);
        loadingText.setFillColor(TEXT_COLOR);
        loadingText.setCharacterSize(52);
        loadingText.setString("Loading...");
        textPositionToCenter = loadingText.getLocalBounds();
        loadingText.setOrigin(textPositionToCenter.width/2, textPositionToCenter.height/2);
        xPos = 0.5f * window.getSize().x;
        yPos = 0.5f * window.getSize().y;
        loadingText.setPosition(xPos, yPos);

        // Les piles de jeu, le nombre de cartes restantes pour chaque pile et les cartes en main.
        ButtonGroup pilesButtonGroup;
        ButtonGroup cardsLeftInPiles;
        ButtonGroup cardsInHand;

        // Groupe contenant les piles de rebut, défausse et deck, ainsi que le nombre de cartes pour chaque.
        ButtonGroup otherPiles;

        // Différents état du tour de jeu. Traduit l'avancement du tour de jeu d'un joueur selon les phases.
        enum RoundState {
            BeginRound,
            ShowHand,
            ActionPhase,
            CardEffect,
            TreasurePhase,
            BuyPhase,
            NextPlayerTurn
        };

        RoundState roundState = BeginRound;

        // Variables utilisées pour le passage des effets de cartes vers l'interface (non utilisées pour l'instant).
        int playedActionCard = -1;
        int cardEffectPhase = -1;
        bool effectIsOver = false;
        bool cardPlayed = false;

        // Boutons de sauvegarde, choix de carte et de saut d'action
        TextButton exitGame = TextButton(0, 0.93f, 0.05f, 180.f, 50.f, "Quit and save", font, 24, window);
        TextButton chooseCardButton = TextButton(0, 0.7f, 0.8f, 180.f, 50.f, "Choose card", font, 24, window);
        TextButton passButton = TextButton(0, 0.7f, 0.9f, 130.f, 50.f, "Pass", font, 24, window);

        // Flèches de défilement des cartes de la main et texte indiquant le nombre de défilements possible.
        TextButton rightArrow = TextButton(0, 0.45f, 0.85f, 40.f, 180.f, ">", font, 24, window);
        sf::Text intervals;
        intervals.setFont(font);
        intervals.setFillColor(TEXT_COLOR);
        int nbIntervals = 1;
        int selectedInterval = 0;
        bool intervalChanged = false;

        // Texte du nom du joueur et de ses données
        sf::Text turnPlayerText;
        turnPlayerText.setFont(font);
        turnPlayerText.setCharacterSize(30);
        turnPlayerText.setFillColor(TEXT_COLOR);
        sf::Text dataPlayerText;
        dataPlayerText.setFont(font);
        dataPlayerText.setCharacterSize(24);
        dataPlayerText.setFillColor(TEXT_COLOR);

        // Différents textes des phases de jeu (Action, Effet de carte, Achat)
        xPos = X_PLAY_TEXT * window.getSize().x;
        yPos = Y_PLAY_TEXT * window.getSize().y;
        sf::Text actionText;
        actionText.setFont(font);
        actionText.setCharacterSize(20);
        actionText.setFillColor(TEXT_COLOR);
        actionText.setString("Which card would you like to play?");
        textPositionToCenter = actionText.getLocalBounds();
        actionText.setOrigin(textPositionToCenter.width/2, textPositionToCenter.height/2);
        actionText.setPosition(xPos, yPos);
        sf::Text cardEffectText;
        cardEffectText.setFont(font);
        cardEffectText.setCharacterSize(20);
        cardEffectText.setFillColor(TEXT_COLOR);
        cardEffectText.setString("Please follow console instructions to use this card's effect.");
        textPositionToCenter = cardEffectText.getLocalBounds();
        cardEffectText.setOrigin(textPositionToCenter.width/2, textPositionToCenter.height/2);
        cardEffectText.setPosition(xPos, yPos);
        sf::Text buyText;
        buyText.setFont(font);
        buyText.setCharacterSize(20);
        buyText.setFillColor(TEXT_COLOR);

        // Numéro de la carte sélectionnée en clic droit
        int cardDetailsPileIndex = -1;
        TextButton returnToGameButton = TextButton(0, 0.92f, 0.05f, 180.f, 50.f, "Return to Game", font, 24, window);

        // Textes de fin de jeu (game over, classement des joueurs et well done) ainsi que le bouton pour revenir à l'écran d'accueil.
        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setCharacterSize(32);
        gameOverText.setFillColor(TEXT_COLOR);
        gameOverText.setString("Game is over! Here are the results.");
        textPositionToCenter = gameOverText.getLocalBounds();
        gameOverText.setOrigin(textPositionToCenter.width/2, textPositionToCenter.height/2);
        xPos = 0.5f * window.getSize().x;
        yPos = 0.2f * window.getSize().y;
        gameOverText.setPosition(xPos, yPos);
        sf::Text playerFinalRankText;
        playerFinalRankText.setFont(font);
        playerFinalRankText.setFillColor(TEXT_COLOR);
        sf::Text wellDoneText;
        wellDoneText.setFont(font);
        wellDoneText.setCharacterSize(32);
        wellDoneText.setFillColor(TEXT_COLOR);
        wellDoneText.setString("Well done!");
        textPositionToCenter = wellDoneText.getLocalBounds();
        wellDoneText.setOrigin(textPositionToCenter.width/2, textPositionToCenter.height/2);
        yPos = 0.7f * window.getSize().y;
        wellDoneText.setPosition(xPos, yPos);
        TextButton backToHomeScreenButton = TextButton(0, 0.5f, 0.8f, 400.f, 50.f, "Go back to home screen", font, 24, window);

        // Boucle principale
        while (window.isOpen())
        {
            // Boucle d'écoute des événements (clics souris, clavier, hover, fermeture de fenêtre, etc.).
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                // Evite de pouvoir redimensionner la fenêtre (jusqu'à implémentation du processus).
                else if (event.type == sf::Event::Resized) {
                    window.setSize(sf::Vector2u(1856, 1024));
                    sf::FloatRect visibleArea(0, 0, 1856, 1024);
                    window.setView(sf::View(visibleArea));
                }

                else if (event.type == sf::Event::MouseButtonPressed) {
                    // Clic gauche de la souris
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2f mousePos = sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y));

                        // Sur le bouton de jeu : on initialise toutes les variables, on passe vers le choix des noms d'utilisateurs.
                        if (playButton.contains(mousePos)) {
                            if(gameState == Resume || gameState == Initial) {
                                nbPlayers = 0;
                                setInitOption = -1;
                                cardChosen = 0;
                                cardName.setString("");
                                chosenCards = {};
                                usedUsernames.clear();
                                players.clear();
                                b.getPlayers().clear();
                                b = Board();
                                boardGenerated = false;
                                currentPlayer = 1;
                                roundState = BeginRound;
                                playedActionCard = -1;
                                cardEffectPhase = -1;
                                effectIsOver = false;
                                cardPlayed = false;
                                pilesButtonGroup.clear();
                                cardsLeftInPiles.clear();
                                nbIntervals = 1;
                                selectedInterval = 0;
                                cardDetailsPileIndex = -1;

                                selectCardNames.clear();
                                float xC = 0.1f;
                                float yC = 0.15f;
                                for(int i = 0; i < static_cast<int>(KingdomCardName::COUNT); i++) {
                                    selectCardNames.addButton(i, xC, yC, 150.f, 50.f, kEnumToString(static_cast<KingdomCardName>(i)), font, 24, window);
                                    xC += 0.11f;
                                    if((i+1) % 8 == 0 && i != 0) { xC = 0.1f; yC += 0.1f; }
                                }

                                nbPlayers = selectNbPlayers.getSelectedValue();
                                setInitOption = selectSetInitMode.getSelectedValue();
                                std::cout << "Selected Set Value: " << setInitOption << std::endl;
                                if (nbPlayers != -1) {
                                    std::cout << "Selected Value: " << nbPlayers << std::endl;
                                    usernameText.setString("What is your username, player " + std::to_string(currentPlayer) + "?: ");
                                    gameState = UsernameInput;
                                } else {
                                    std::cout << "No button selected." << std::endl;
                                }
                            }
                        }

                        // Sur le bouton continuer la partie : on reprend la partie là où elle s'était arrêtée
                        if(resumeButton.contains(mousePos) && gameState == Resume) {
                            b = bSave;
                            gameState = RoundPlayer;
                        }

                        // Sur le bouton suivant : on passe au choix de nom de joueur ou de carte Royaume suivant
                        if(nextButton.contains(mousePos)) {
                            if(gameState == UsernameInput) {
                                if(userInputField.getContent() != "" && usedUsernames.insert(userInputField.getContent()).second) {
                                    players.push_back(new Player{userInputField.getContent()});
                                    userInputField.clear();
                                    currentPlayer++;
                                } else {
                                    // display error message for some time?
                                }
                                usernameText.setString("What is your username, player " + std::to_string(currentPlayer) + "?: ");
                                if(currentPlayer > nbPlayers) {
                                    gameState = SetGeneration;
                                    // Choix aléatoire des cartes
                                    if(setInitOption == 0) {
                                        piles = Set::getSetCards(nbPlayers);
                                        gameState = Loading;
                                    }
                                }
                            }
                            else if(gameState == SetGeneration) {
                                if(setInitOption == 0) {
                                // Choix du set de 10 cartes
                                } else if(setInitOption == 1) {
                                    piles = Set::getSetCards(nbPlayers, static_cast<SetName>(selectSetName.getSelectedValue()));
                                    gameState = Loading;
                                // Choix des 10 cartes par nom
                                } else if(setInitOption == 2) {
                                    if(cardChosen < 10) {
                                        std::cout << "Selected Card Value: " << selectCardNames.getSelectedValue() << std::endl;
                                        if(selectCardNames.getSelectedValue() != -1) {
                                            chosenCards.push_back(static_cast<KingdomCardName>(selectCardNames.getSelectedValue()));
                                            if(cardName.getString().toAnsiString() == "") {
                                                cardName.setString(kEnumToString(static_cast<KingdomCardName>(selectCardNames.getSelectedValue())));
                                            } else {
                                                cardName.setString(cardName.getString().toAnsiString() + " - " + kEnumToString(static_cast<KingdomCardName>(selectCardNames.getSelectedValue())));
                                            }
                                            selectCardNames.removeButtonByValue(selectCardNames.getSelectedValue());
                                            sf::FloatRect rect = cardName.getLocalBounds();
                                            cardName.setOrigin(rect.width/2, rect.height/2);
                                            float y = 0.05f * window.getSize().y;
                                            float x = 0.5f * window.getSize().x;
                                            cardName.setPosition(x, y);
                                            cardChosen++;
                                        }
                                    }
                                    // Si les 10 cartes choisies sont bien différentes, on continue, sinon on recommence le choix (à modifier pour empêcher à l'avance l'utilisateur de choisir un carte en double).
                                    if(cardChosen == 10) {
                                        piles = Set::getSetCards(nbPlayers, chosenCards.at(0), chosenCards.at(1), chosenCards.at(2),
                                                                chosenCards.at(3), chosenCards.at(4), chosenCards.at(5),
                                                                chosenCards.at(6), chosenCards.at(7), chosenCards.at(8), chosenCards.at(9));
                                        if(piles.empty()) {
                                            chosenCards = {};
                                            cardChosen = 0;
                                            cardName.setString("");
                                        } else {
                                            gameState = Loading;
                                        }
                                    }
                                } else {
                                    piles = Set::getSetCards(nbPlayers, SetName::Base);
                                    gameState = Loading;
                                }
                            }
                        }

                        if(rightArrow.contains(mousePos) && gameState == RoundPlayer) {
                            if(selectedInterval+1 >= nbIntervals) {
                                selectedInterval = 0;
                            } else {
                                selectedInterval++;
                            }
                            intervalChanged = true;
                        }

                        // Sur le bouton de choix de carte en jeu.
                        if(chooseCardButton.contains(mousePos) && gameState == RoundPlayer) {
                            // On vérifie que la carte sélectionnée est une carte Action et qu'elle existe avant de la jouer.
                            if(roundState == ActionPhase) {
                                if(b.getCurrentPlayer()->showCard(cardsInHand.getSelectedValue()) != NULL && b.getCurrentPlayer()->showCard(cardsInHand.getSelectedValue())->isActionCard()) {
                                    playedActionCard = playedActionCard;
                                    effectIsOver = effectIsOver;
                                    cardEffectPhase++;
                                    // playedActionCard = cardsInHand.getSelectedValue();
                                    // roundState = CardEffect;
                                }
                            }
                            // Pas utilisé pour l'instant
                            if(roundState == CardEffect) {
                                // if(b.getCurrentPlayer()->showCard(cardsInHand.getSelectedValue())->isActionCard()) {
                                //     cardEffectPhase++;
                                //     effectIsOver = b.getCurrentPlayer()->playActionCard(playedActionCard, cardEffectPhase, pilesButtonGroup.getSelectedValue(), cardsInHand.getSelectedValue());
                                // }
                            }
                            // On vérifie que la carte sélectionnée peut être achetée avant de procéder à l'achat.
                            if(roundState == BuyPhase) {
                                Card *c = b.chooseCard(b.getCurrentPlayer()->getNbCoins(), pilesButtonGroup.getSelectedValue());
                                if(c != NULL) {
                                    b.getCurrentPlayer()->getNewCard(c, false);
                                }
                            }
                            selectedInterval = 0;
                        }

                        // Sur le bouton de passage de l'action. On passe directement à la phase de jeu suivante sans rien faire.
                        if(passButton.contains(mousePos) && gameState == RoundPlayer) {
                            if(roundState == ActionPhase) { roundState = TreasurePhase; }
                            if(roundState == CardEffect) { /*cardEffectPhase++;*/ }
                            if(roundState == BuyPhase) { roundState = NextPlayerTurn; }
                            selectedInterval = 0;
                        }

                        // Sur le bouton de sauvegarde : on revient à l'écran d'accueil.
                        if(exitGame.contains(mousePos) && gameState == RoundPlayer) {
                            bSave = b;
                            gameState = Resume;
                        }

                        // Sur le bouton pour quitter l'interface de détails de carte.
                        if(returnToGameButton.contains(mousePos) && gameState == CardDetails) {
                            cardDetailsPileIndex = -1;
                            gameState = RoundPlayer;
                        }

                        // Sur le bouton de retour à l'écran d'accueil en fin de partie.
                        if(backToHomeScreenButton.contains(mousePos) && gameState == Results) {
                            gameState = Initial;
                        }
                    }

                    // Clic droit de la souris
                    else if(event.mouseButton.button == sf::Mouse::Right) {
                        sf::Vector2f mousePos = sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y));

                        // Récupère la valeur de la pile cliquée et passe en mode détails de la carte.
                        cardDetailsPileIndex = pilesButtonGroup.getValueAtPosition(mousePos);
                        if(cardDetailsPileIndex != -1) {
                            gameState = CardDetails;
                        }
                    }
                }

                // Lors de l'écriture de texte, on met à jour le champ de saisie.
                else if (event.type == sf::Event::TextEntered) {
                    userInputField.handleEvent(event);
                }

                // Permettre aux groupes de boutons d'écouter le bouton sélectionné par l'utilisateur.
                selectNbPlayers.handleEvent(event, window);
                selectSetInitMode.handleEvent(event, window);
                selectSetName.handleEvent(event, window);
                selectCardNames.handleEvent(event, window);
                pilesButtonGroup.handleEvent(event, window);
                cardsInHand.handleEvent(event, window);
            }

            // A chaque passage dans la boucle while principale, on efface et redessine tout, selon l'étape de jeu à laquelle on se trouve.
            window.clear();
            window.draw(sprite);

            if(gameState == Initial) {
                playButton.draw(window);
                window.draw(chooseOptionsText);
                selectNbPlayers.draw(window);
                selectSetInitMode.draw(window);
            }

            if(gameState == Resume) {
                playButton.draw(window);
                resumeButton.draw(window);
                selectNbPlayers.draw(window);
                selectSetInitMode.draw(window);
            }

            if(gameState == UsernameInput) {
                textPositionToCenter = usernameText.getLocalBounds();
                usernameText.setOrigin(textPositionToCenter.width/2, textPositionToCenter.height/2);
                xPos = 0.5f * window.getSize().x;
                yPos = 0.5f * window.getSize().y;
                usernameText.setPosition(xPos, yPos);
                nextButton.draw(window);
                window.draw(usernameText);
                userInputField.draw(window);
            }

            if(gameState == SetGeneration) {
                if(setInitOption == 0) {
                } else if(setInitOption == 1) {
                    selectSetName.draw(window);
                } else if(setInitOption == 2) {
                    selectCardNames.draw(window);
                    window.draw(cardName);
                } else {
                }
                if(setInitOption != 0) { nextButton.draw(window); }
            }

            // Genère le plateau de jeu initialisé et l'affiche sur l'interface avec un temps d'attente pour permettre à tous les joueurs de l'observer avant le début de la partie.
            if(gameState == NewBoard) {
                int t;
                if(!boardGenerated) {
                    t = 0;
                    b = Board(players);
                    std::vector<Card*> baseDeck = Set::getBaseDeck();
                    b.initializeBoard(baseDeck, piles);
                    int i = 0;
                    float x = X_PILES_BOARD;
                    float y = Y_PILES_BOARD;
                    for(Pile p : piles) {
                        if(!p.isEmpty()) {
                            sf::Texture cardTexture;
                            cardTexture.loadFromFile("assets/" + p.showCard(0)->getTitle() + ".jpg");
                            cardsTextureMap.insert(std::make_pair(p.showCard(0)->getTitle(), cardTexture));
                            pilesButtonGroup.addButton(i, x, y, 0.1f, cardsTextureMap.at(p.showCard(0)->getTitle()), window);
                        }
                        i++;
                        x += X_OFFSET_CARD;
                        if(i % 6 == 0) { x = X_PILES_BOARD; y += Y_OFFSET_CARD; }
                    }
                    boardGenerated = true;
                }
                if(t >= 100) { gameState = RoundPlayer; }
                pilesButtonGroup.draw(window);
                t++;
            }

            // Tour de jeu d'un joueur et écoute de la fin de partie.
            if(gameState == RoundPlayer) {
                if(b.gameIsOver()) {
                    gameState = Results;
                }

                int tp;

                Player* p = b.getCurrentPlayer();

                // Affichage des éléments à l'écran

                turnPlayerText.setString(p->getUsername());
                textPositionToCenter = turnPlayerText.getLocalBounds();
                turnPlayerText.setOrigin(textPositionToCenter.width/2, textPositionToCenter.height/2);
                xPos = X_PLAYER_INFO * window.getSize().x;
                yPos = 0.14f * window.getSize().y;
                turnPlayerText.setPosition(xPos, yPos);
                dataPlayerText.setString("\nActions: " + std::to_string(p->getNbActions()) +
                                        "\nBuys: " + std::to_string(p->getNbBuys()) +
                                        "\nCoins: " + std::to_string(p->getNbCoins()) +
                                        "\nVictory: " + std::to_string(p->getTotalVictoryPoints()));
                textPositionToCenter = dataPlayerText.getLocalBounds();
                dataPlayerText.setOrigin(textPositionToCenter.width/2, textPositionToCenter.height/2);
                xPos = X_PLAYER_INFO * window.getSize().x;
                yPos = 0.22f * window.getSize().y;
                dataPlayerText.setPosition(xPos, yPos);

                nbIntervals = p->getNbCardsInHand() / 5;
                if(p->getNbCardsInHand() % 5 != 0) { nbIntervals++; }
                int j = selectedInterval*5;
                int k = selectedInterval+1 == nbIntervals ? p->getNbCardsInHand() : j+5;
                // std::cout << "p: " << p->getNbCardsInHand() << " k: " << k << std::endl;
                intervals.setString(std::to_string(selectedInterval+1) + "/" + std::to_string(nbIntervals));
                sf::FloatRect rectInt = intervals.getLocalBounds();
                intervals.setOrigin(rectInt.width/2, rectInt.height/2);
                float yPosInt = 0.85f * window.getSize().y;
                float xPosInt = 0.5f * window.getSize().x;
                intervals.setPosition(xPosInt, yPosInt);


                if(roundState != ActionPhase || (roundState == ActionPhase && intervalChanged) || (roundState == ActionPhase && cardPlayed)) {
                    cardsInHand.clear();
                    float x = X_PILES_BOARD;
                    if(p->getNbCardsInHand() != 0) {
                        for(int i = j; i < k; i++) {
                            cardsInHand.addButton(i, x, 0.75f, 0.1f, cardsTextureMap.at(p->showCard(i)->getTitle()), window);
                            x += X_OFFSET_CARD;
                        }
                        cardsInHand.draw(window);
                        intervalChanged = false;
                        cardPlayed = false;
                    }
                } else {
                    cardsInHand.draw(window);
                }

                int i = 0;
                float x2 = X_PILES_BOARD;
                float y2 = Y_PILES_BOARD;
                cardsLeftInPiles.clear();
                for(Pile p : b.getPiles()) {
                    cardsLeftInPiles.addButton(i, x2+0.009f, y2+0.016f, 30.f, 30.f, std::to_string(p.getNbCards()), font, 16, window);
                    i++;
                    x2 += X_OFFSET_CARD;
                    if(i % 6 == 0) { x2 = X_PILES_BOARD; y2 += Y_OFFSET_CARD; }
                }
                cardsLeftInPiles.setSelectedValue(-1);

                otherPiles.clear();
                if(p->getNbCardsInDeck() > 0) {
                    otherPiles.addButton(0, 0.82f, 0.75f, 0.52f, CardBackTexture, window); // deck
                    otherPiles.addButton(1, 0.82f+X_OFFSET_LABEL_D, 0.75f+Y_OFFSET_LABEL, 127.f, 40.f, "Deck: " + std::to_string(p->getNbCardsInDeck()), font, 22, window);
                }
                if(p->getNbCardsInDiscard() > 0) {
                    otherPiles.addButton(2, 0.9f, 0.75f, 0.1f, cardsTextureMap.at(p->showTitleLastCardInDiscard()), window); // discard
                    otherPiles.addButton(3, 0.9f+X_OFFSET_LABEL_TD, 0.75f+Y_OFFSET_LABEL, 120.f, 40.f, "Discard: " + std::to_string(p->getNbCardsInDiscard()), font, 22, window);
                }
                if(b.getNbCardsInTrash() > 0) {
                    otherPiles.addButton(4, X_PILES_BOARD+(5*X_OFFSET_CARD), Y_PILES_BOARD+(2*Y_OFFSET_CARD), 0.1f, cardsTextureMap.at(b.showTitleLastCardInTrash()), window); // trash
                    otherPiles.addButton(5, X_PILES_BOARD+(5*X_OFFSET_CARD)+X_OFFSET_LABEL_TD, Y_PILES_BOARD+(2*Y_OFFSET_CARD)+Y_OFFSET_LABEL, 120.f, 40.f, "Trash: " + std::to_string(b.getNbCardsInTrash()), font, 22, window);
                }

                pilesButtonGroup.draw(window);
                window.draw(turnPlayerText);
                window.draw(dataPlayerText);
                cardsLeftInPiles.draw(window);
                otherPiles.draw(window);
                if(p->getNbCardsInHand() > 5) {
                    rightArrow.draw(window);
                    window.draw(intervals);
                }

                // Définition des comportements et des affichages supplémentaires selon les phases de jeu.

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
                    exitGame.draw(window);
                }

                if(roundState == ActionPhase) {
                    // Carte jouée mais nécessite un choix du joueur sur la console (affichage du texte correspondant).
                    if(cardEffectPhase >= 0) {
                        window.draw(cardEffectText);
                        cardEffectPhase = -2;
                    // Carte pas encore jouée (choix de cette valeur pour cardEffectPhase afin qu'un premier passage dans la boucle affiche de message au-dessus avant de jouer la carte et potentiellement devoir passer sur la console).
                    } else if(cardEffectPhase < -1) {
                        cardPlayed = b.getCurrentPlayer()->playCard(cardsInHand.getSelectedValue());
                        std::cout << std::endl;
                        cardEffectPhase = -1;
                    // Aucune carte jouée et attente d'un choix du joueur (ou bien pas de cartes Action et la phase de jeu suivante se lance).
                    } else {
                        if(p->hasActionCards() && p->getNbActions() > 0) {
                            window.draw(actionText);
                        } else {
                            roundState = TreasurePhase;
                        }
                        cardEffectPhase = -1;
                    }
                    playedActionCard = -1;
                    effectIsOver = false;
                }

                // Pas utilisé pour l'instant
                if(roundState == CardEffect) {
                    // if(p->showCard(playedActionCard)->isActionCard()) {
                    //     cardEffectText.setString(dynamic_cast<Action*>(p->showCard(playedActionCard))->getEffectText());
                    //     float x = 0.5f * (window.getSize().x - actionText.getLocalBounds().width);
                    //     float y = 0.7f * window.getSize().y;
                    //     cardEffectText.setPosition(x, y);
                    // }
                    // window.draw(cardEffectText);
                    // if(effectIsOver) { roundState = ActionPhase; }
                }

                // Joue les cartes Trésor de la main du joueur et ajoute le nombre de pièces en conséquence avant de passer à la phase d'achat.
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
                    }
                    roundState = BuyPhase;
                }

                if(roundState == BuyPhase) {
                    if(p->getNbBuys() <= 0) {
                        roundState = NextPlayerTurn;
                    }
                    xPos = X_PLAY_TEXT * window.getSize().x;
                    yPos = Y_PLAY_TEXT * window.getSize().y;
                    buyText.setString("Which card would you like to buy (you have " + std::to_string(p->getNbCoins()) + " coins)?");
                    textPositionToCenter = buyText.getLocalBounds();
                    buyText.setOrigin(textPositionToCenter.width/2, textPositionToCenter.height/2);
                    buyText.setPosition(xPos, yPos);
                    window.draw(buyText);
                }

                if(roundState == NextPlayerTurn) {
                    p->finishRound();
                    b.nextPlayerRound();
                    roundState = BeginRound;
                }
            }

            // Affiche en grand la carte sur l'écran, les détails (notamment son effet) sont lisibles facilement.
            if(gameState == CardDetails) {
                Card *c = piles.at(cardDetailsPileIndex).showCard(0);
                if(c != NULL) {
                    ImageButton cardDetails = ImageButton(0, 0.3f, 0.03f, 0.48f, cardsTextureMap.at(c->getTitle()), window);
                    cardDetails.draw(window);
                    returnToGameButton.draw(window);
                } else {
                    cardDetailsPileIndex = -1;
                    gameState = RoundPlayer;
                }
                
            }

            if(gameState == Results) {
                // TODO Ne trie pas correctement...
                players = b.getPlayers();
                std::sort(players.rbegin(), players.rend(), [](const Player* l, const Player* r) {
                    return l->getTotalVictoryPoints() < r->getTotalVictoryPoints();
                });
                for(int i = 1; i <= int(b.getPlayers().size()); i++) {
                    playerFinalRankText.setString(std::to_string(i) + ": " + b.getPlayers().at(i-1)->getUsername() + " with " + std::to_string(b.getPlayers().at(i-1)->getTotalVictoryPoints()) + " VP");
                    sf::FloatRect rectRanking = playerFinalRankText.getLocalBounds();
                    playerFinalRankText.setOrigin(rectRanking.width/2, rectRanking.height/2);
                    float x = 0.5f * window.getSize().x;
                    float y = 0.1 * (i + 2) * window.getSize().y;
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

            // Affichage de la fenêtre à l'écran avec tous les composants dessinés dessus.
            window.display();

        }

    } else {
        // CLI

        // Choix du nombre de joueurs par l'utilisateur.
        while(nbPlayers < 2 || nbPlayers > 4) {
            std::cout << "How many players are you? (2 to 4): ";
            std::cin >> nbPlayers;

            if(std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                nbPlayers = 0;
            }
        }

        // Choix des noms d'utilisateurs uniques.
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

        // Choix du mode de sélection des 10 cartes Royaume.
        std::cout << "\nHow do you want to choose Kingdom cards?\n0: Randomly\n1: Set Name\n2: Each Card Name" << std::endl;
        while(setInitOption < 0 || setInitOption > 2) {
            std::cout << "Your choice: ";
            std::cin >> setInitOption;

            if(std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                setInitOption = -1;
            }
        }

        std::vector<Card*> baseDeck = Set::getBaseDeck();
        std::vector<Pile> piles = {};

        // 10 cartes Royaume aléatoires.
        if(setInitOption == 0) { piles = Set::getSetCards(nbPlayers); }
        // 10 cartes Royaume d'un set prédéfini.
        if(setInitOption == 1) {
            setInitOption = -1;
            while(setInitOption < 0 || setInitOption > static_cast<int>(SetName::COUNT)-1) {
                std::cout << "\nWhich Set would you like to use?: " << std::endl;
                for(int i = 0; i < static_cast<int>(SetName::COUNT); i++) {
                    std::cout << i << ": " << sEnumToString(static_cast<SetName>(i)) << std::endl;
                }
                std::cout << "Your choice: ";
                std::cin >> setInitOption;

                if(std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    setInitOption = -1;
                }
            }
            piles = Set::getSetCards(nbPlayers, static_cast<SetName>(setInitOption));
        }
        // 10 cartes Royaume par nom de carte.
        if(setInitOption == 2) {
            while(piles.empty()) {
                chosenCards = {};
                for(int i = 0; i < 10; i++) {
                    setInitOption = -1;
                    while(setInitOption < 0 || setInitOption > static_cast<int>(KingdomCardName::COUNT)-1) {
                        std::cout << std::endl;
                        for(int i = 0; i < static_cast<int>(KingdomCardName::COUNT); i++) {
                            std::cout << i << ": " << kEnumToString(static_cast<KingdomCardName>(i)) << std::endl;
                        }
                        std::cout << "Which Kingdom Card " << i+1 << " would you like to use?: ";
                        std::cin >> setInitOption;

                        if(std::cin.fail()) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            setInitOption = -1;
                        }
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

        // Initialisation du plateau de jeu avec les informations nécessaires.
        b.initializeBoard(baseDeck, piles);

        system("clear");

        // Ecoute de la condition de fin de partie. Chaque joueur joue son tour l'un après l'autre.
        while(!b.gameIsOver()) {
            std::cout << b << std::endl;
            b.playRound();
            // Nettoyage de la console après chaque tour de jeu pour plus de clarté (peut plus ou moins bien marcher selon l'OS ? clear est un mot clé de console universel ?).
            system("clear");
        }

        // Affichage des résultats à la fin de la partie.
        b.showResults();
    }

    return 0;
}