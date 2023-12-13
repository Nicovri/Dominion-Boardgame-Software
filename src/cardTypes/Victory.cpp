#include "Victory.hpp"

Victory::Victory(int price, std::string title, bool isVisible, int points): Card(price, title, isVisible), Point(points) {}

bool Victory::isActionCard() { return false; }

bool Victory::isTreasureCard() { return false; }

bool Victory::isVictoryCard() { return true; }