#include "Treasure.hpp"

Treasure::Treasure(int price, std::string title, bool isVisible, int points): Card(price, title, isVisible), points(points) {}

int Treasure::getNumberPoints() const { return points.getNumberPoints(); }

bool Treasure::isActionCard() { return false; }

bool Treasure::isTreasureCard() { return true; }

bool Treasure::isVictoryCard() { return false; }

bool Treasure::isAttackCard() { return false; }

bool Treasure::isReactionCard() { return false; }