#pragma once

#include "../cardTypes/Treasure.hpp"

class Copper: public Treasure {

public:
    Copper();
    void play(Board &b);
};