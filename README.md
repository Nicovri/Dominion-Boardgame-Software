# Dominion-Boardgame-Software

## (English Description)

This project is a desktop software version of the Dominion card game, implemented in C++ and designed to compile on Linux. The game provides both a Command Line Interface (CLI) version and a Graphic User Interface (GUI) version.

## Prerequisites

Before running the software, make sure you have the SFML graphic library installed. You can install it using the following command (for other Linux distributions, look up in their docs):

```bash
sudo apt-get install libsfml-dev
```

If you have a previous version of SFML installed, uninstall it before proceeding.

Alternatively, you can download SFML version 2.6 from the official SFML website. Copy the contents of the `SFML-2.6/include` folder to `/usr/include` and the contents of the `SFML-2.6/lib` folder to `/usr/lib`.

## Running the Software

To compile and run the CLI version, navigate to the project folder and execute:

```bash
make run
```

For the GUI version, use the following command:

```bash
make run ARGS="1 0"
```

ARGS takes 2 integers:

- 1 for GUI and anything else for CLI
- the second integer is a background choice. If nothing given, it is chosen randomly. 0 corresponds to base background, the most neutral.

---

## (Description en français)

Ce projet est une version logicielle du jeu de cartes Dominion, développée en C++ et conçue pour être compilée sur Linux. Le jeu propose une version en Interface en Ligne de Commande (CLI) ainsi qu'une version en Interface Graphique (GUI).

## Prérequis

Avant d'exécuter le logiciel, assurez-vous d'avoir la bibliothèque graphique SFML installée. Vous pouvez l'installer en utilisant la commande suivante (avec une autre distribution Linux, regardez dans leur documentation):

```bash
sudo apt-get install libsfml-dev
```

Si vous avez une version précédente de SFML installée, désinstallez-la avant de continuer.

Alternativement, vous pouvez télécharger la version 2.6 de SFML depuis le site officiel de SFML. Copiez le contenu du dossier `SFML-2.6/include` dans `/usr/include` et le contenu du dossier `SFML-2.6/lib` dans `/usr/lib`.

## Exécution du logiciel

Pour compiler et exécuter la version CLI, accédez au dossier du projet et exécutez la commande :

```bash
make run
```

Pour la version GUI, utilisez la commande suivante :

```bash
make run ARGS="1 0"
```

ARGS prend 2 entiers :

- 1 pour le mode GUI et autre chose pour le mode CLI
- le deuxième entier est un choix de fond d'écran. Si rien n'est donné, il est choisi aléatoirement. 0 correspond au fond d'écran de base, le plus neutre.
