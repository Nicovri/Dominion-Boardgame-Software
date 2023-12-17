#pragma once

#include "../cardTypes/Victory.hpp"

class Duchy: public Victory {

public:
    Duchy();
    void play(Board &b);
};