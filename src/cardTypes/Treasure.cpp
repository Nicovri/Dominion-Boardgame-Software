#include "Treasure.hpp"

Treasure::Treasure(int price, std::string title, bool isVisible, int points): Card(price, title, isVisible), Point(points) {}

bool Treasure::isActionCard() { return false; }

bool Treasure::isTreasureCard() { return true; }

bool Treasure::isVictoryCard() { return false; }