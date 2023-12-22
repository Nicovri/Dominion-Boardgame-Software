#include "Button.hpp"

Button::Button(int value): isSelected(true), value(value) {}

bool Button::getSelected() const { return isSelected; }

int Button::getValue() const { return value; }

void Button::setSelected(bool selected) { isSelected = selected; }

void Button::setValue(int value) { this->value = value; }