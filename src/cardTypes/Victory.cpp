#include "Victory.hpp"

Victory::Victory(int price, std::string title, bool isVisible, int points): Card(price, title, isVisible), points(points) {}

int Victory::getNumberPoints() const { return points.getNumberPoints(); }

bool Victory::isActionCard() { return false; }

bool Victory::isTreasureCard() { return false; }

bool Victory::isVictoryCard() { return true; }

bool Victory::isAttackCard() { return false; }

bool Victory::isReactionCard() { return false; }