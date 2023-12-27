#pragma once

#include "../cardTypes/Victory.hpp"
#include "../enums.hpp"

// Classe des cartes Province, sous-classe de Victory.
class Province: public Victory {

public:
    Province();
    void play(Board &b);
};