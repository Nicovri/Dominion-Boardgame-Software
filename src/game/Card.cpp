#include "Card.hpp"

Card::Card() {}

Card::Card(int price, std::string title, bool isVisible): price(price), title(title), isVisible(isVisible) {}

bool Card::isActionCard() { return false; }

bool Card::isTreasureCard() { return false; }

bool Card::isVictoryCard() { return false; }

std::ostream& operator<<(std::ostream &os, const Card &c) {
    if(c.isVisible) {
        os << c.title << ": price=" << c.price;
    } else {
        os << "Card is hidden" << std::endl;
    }
    return os;
}