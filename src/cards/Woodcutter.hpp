#pragma once

#include "../cardTypes/Action.hpp"

class Woodcutter: public Action {

public:
    Woodcutter();
    void play(Board &b);
};