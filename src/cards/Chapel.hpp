#pragma once

#include "../cardTypes/Action.hpp"
#include <iostream>

class Chapel: public Action {

public:
    Chapel();
    void play(Board &b);
};