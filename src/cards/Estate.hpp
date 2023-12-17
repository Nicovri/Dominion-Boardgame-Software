#pragma once

#include "../cardTypes/Victory.hpp"

class Estate: public Victory {

public:
    Estate();
    void play(Board &b);
};