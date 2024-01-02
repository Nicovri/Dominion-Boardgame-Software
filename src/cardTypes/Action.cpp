#include "Action.hpp"

Action::Action(int price, std::string title, bool isVisible): Card(price, title, isVisible) {}

Action::Action(int price, std::string title, bool isVisible, std::string effectText): Card(price, title, isVisible), effectText(effectText) {}

std::string Action::getEffectText() const { return this->effectText; }

bool Action::isActionCard() { return true; }

bool Action::isTreasureCard() { return false; }

bool Action::isVictoryCard() { return false; }

bool Action::isAttackCard() { return false; }

bool Action::isReactionCard() { return false; }