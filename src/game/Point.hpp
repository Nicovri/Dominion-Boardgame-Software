#pragma once

#include <iostream>

// Classe retournant un certain nombre de points. Particulièrement utile pour des cartes de type Victoire et Trésor en même temps.
class Point {
    int number;

public:
    Point(int num);
    virtual int getNumberPoints() const;

    friend std::ostream& operator<<(std::ostream &os, Point &p);
};