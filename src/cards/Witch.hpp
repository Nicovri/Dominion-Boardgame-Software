#pragma once

#include "../cardTypes/Action.hpp"

class Witch: public Action {

public:
    Witch();
    void play(Board &b);
};