#include "Reaction.hpp"

Reaction::Reaction(int price, std::string title, bool isVisible, int conditionTriggered): Card(price, title, isVisible), conditionTriggered(conditionTriggered) {}

int Reaction::getConditionTriggered() const { return conditionTriggered; }

bool Reaction::isActionCard() { return false; }

bool Reaction::isTreasureCard() { return false; }

bool Reaction::isVictoryCard() { return false; }

bool Reaction::isAttackCard() { return false; }

bool Reaction::isReactionCard() { return true; }

bool Reaction::react([[maybe_unused]] Board &b, Player *p) {
    std::string choice = "";
    while(choice == "" || (choice != "Y" && choice != "N")) {
        std::cout << p->getUsername() << ", would you like to play this Reaction card's effect: " << this->getTitle() << " (Y/N)?: ";
        std::cin >> choice;
    }

    if(choice == "Y") {
        return true;
    }
    return false;
}