#pragma once

#include "../cardTypes/Action.hpp"

class Remodel: public Action {

public:
    Remodel();
    void play(Board &b);
};