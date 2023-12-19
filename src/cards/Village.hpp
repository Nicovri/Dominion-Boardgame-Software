#pragma once

#include "../cardTypes/Action.hpp"

class Village: public Action {

public:
    Village();
    void play(Board &b);
};