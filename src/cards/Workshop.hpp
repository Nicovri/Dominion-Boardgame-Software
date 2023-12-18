#pragma once

#include "../cardTypes/Action.hpp"

class Workshop: public Action {

public:
    Workshop();
    void play(Board &b);
};