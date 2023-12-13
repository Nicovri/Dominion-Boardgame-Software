#include "Point.hpp"

Point::Point(int num): number(num) {}

int Point::getNumberPoints() const { return this->number; }

std::ostream& operator<<(std::ostream &os, Point &p) {
    return os << "points=" << p.number;
}