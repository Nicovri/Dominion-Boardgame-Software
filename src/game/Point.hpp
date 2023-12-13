#pragma once

#include <iostream>

class Point {
    int number;

public:
    Point(int num);
    int getNumberPoints() const;

    friend std::ostream& operator<<(std::ostream &os, Point &p);
};