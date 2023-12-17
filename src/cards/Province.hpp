#pragma once

#include "../cardTypes/Victory.hpp"

class Province: public Victory {

public:
    Province();
    void play(Board &b);
};