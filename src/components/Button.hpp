#pragma once

#include <SFML/Graphics.hpp>

// Classe abstraite représentant un bouton sur l'interface SFML.
class Button {
    bool isSelected;
    int value;

public:
    Button(int value);
    bool getSelected() const;
    int getValue() const;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void setValue(int value);
    virtual void setSelected(bool selected);
    virtual bool contains(const sf::Vector2f& point) const = 0;
    virtual void setPositionRelativeToWindow(float relativeX, float relativeY, sf::RenderWindow& window) = 0;
};