#include "Action.hpp"

Action::Action(int price, std::string title, bool isVisible): Card(price, title, isVisible) {}

bool Action::isActionCard() { return true; }

bool Action::isTreasureCard() { return false; }

bool Action::isVictoryCard() { return false; }

void Action::useEffect() {}