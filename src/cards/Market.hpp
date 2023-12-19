#pragma once

#include "../cardTypes/Action.hpp"

class Market: public Action {

public:
    Market();
    void play(Board &b);
};