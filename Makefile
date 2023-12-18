CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -std=c++11

SRCDIR=./src
BUILDDIR=./build
CARDSDIR=$(BUILDDIR)/cards

# compile:
# 	$(CXX) -Isfml/include -c ./src/main.cpp
# 	$(CXX) ./build/main.o -o sfml-app -Lsfml/lib -lsfml-graphics -lsfml-window -lsfml-system
# # ???

$(BUILDDIR)/%.o: $(SRCDIR)/game/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/cardTypes/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/cards/%.o: $(SRCDIR)/cards/%.cpp | $(CARDSDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR)/dominion-game: $(BUILDDIR)/main.o $(BUILDDIR)/enums.o $(BUILDDIR)/Board.o $(BUILDDIR)/Set.o $(BUILDDIR)/Player.o $(BUILDDIR)/Card.o $(BUILDDIR)/Pile.o $(BUILDDIR)/Point.o $(BUILDDIR)/Victory.o $(BUILDDIR)/Treasure.o $(BUILDDIR)/Action.o $(CARDSDIR)/Curse.o $(CARDSDIR)/Estate.o $(CARDSDIR)/Duchy.o $(CARDSDIR)/Province.o $(CARDSDIR)/Copper.o $(CARDSDIR)/Silver.o $(CARDSDIR)/Gold.o $(CARDSDIR)/Workshop.o $(CARDSDIR)/Woodcutter.o
	$(CXX) $^ -o $@

.PHONY: run clean

run: $(BUILDDIR)/dominion-game
	./$< $(ARGS)

clean:
	rm -rf $(BUILDDIR)

$(BUILDDIR):
	mkdir build

$(CARDSDIR):
	mkdir build/cards