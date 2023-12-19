#pragma once

#include "../cardTypes/Action.hpp"

class Smithy: public Action {

public:
    Smithy();
    void play(Board &b);
};