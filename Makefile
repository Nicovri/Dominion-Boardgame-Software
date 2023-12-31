CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -std=c++11

SRCDIR=./src
BUILDDIR=./build
CARDSDIR=$(BUILDDIR)/cards
SFMLDIR=$(BUILDDIR)/components

MAIN := $(BUILDDIR)/main.o
ENUMS := $(BUILDDIR)/enums.o
COMPONENTS := $(SFMLDIR)/Button.o $(SFMLDIR)/TextButton.o $(SFMLDIR)/ImageButton.o $(SFMLDIR)/ButtonGroup.o $(SFMLDIR)/TextInputField.o
GAME := $(BUILDDIR)/Board.o $(BUILDDIR)/Set.o $(BUILDDIR)/Player.o $(BUILDDIR)/Card.o $(BUILDDIR)/Pile.o $(BUILDDIR)/Point.o
CARDTYPES := $(BUILDDIR)/Victory.o $(BUILDDIR)/Treasure.o $(BUILDDIR)/Action.o
VICTORY_CARDS := $(CARDSDIR)/Curse.o $(CARDSDIR)/Estate.o $(CARDSDIR)/Duchy.o $(CARDSDIR)/Province.o $(CARDSDIR)/Gardens.o
TREASURE_CARDS := $(CARDSDIR)/Copper.o $(CARDSDIR)/Silver.o $(CARDSDIR)/Gold.o
ACTION_CARDS := $(CARDSDIR)/Workshop.o $(CARDSDIR)/Woodcutter.o $(CARDSDIR)/Cellar.o $(CARDSDIR)/Chapel.o $(CARDSDIR)/Smithy.o $(CARDSDIR)/Market.o $(CARDSDIR)/Mine.o $(CARDSDIR)/Remodel.o $(CARDSDIR)/Witch.o $(CARDSDIR)/Village.o $(CARDSDIR)/Festival.o $(CARDSDIR)/Laboratory.o $(CARDSDIR)/Moneylender.o $(CARDSDIR)/CouncilRoom.o $(CARDSDIR)/Militia.o $(CARDSDIR)/Poacher.o $(CARDSDIR)/Feast.o $(CARDSDIR)/Bandit.o $(CARDSDIR)/Artisan.o

$(BUILDDIR)/%.o: $(SRCDIR)/game/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/cardTypes/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/cards/%.o: $(SRCDIR)/cards/%.cpp | $(CARDSDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/main.o: $(SRCDIR)/main.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -I/usr/include/SFML -c $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/components/%.o: $(SRCDIR)/components/%.cpp | $(SFMLDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/dominion-game: $(MAIN) $(ENUMS) $(COMPONENTS) $(GAME) $(CARDTYPES) $(VICTORY_CARDS) $(TREASURE_CARDS) $(ACTION_CARDS)
	$(CXX) $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: run clean

run: $(BUILDDIR)/dominion-game
	./$< $(ARGS)

clean:
	rm -rf $(BUILDDIR)

$(BUILDDIR):
	mkdir build

$(CARDSDIR):
	mkdir build/cards

$(SFMLDIR):
	mkdir build/components