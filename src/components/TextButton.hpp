#pragma once

#include <SFML/Graphics.hpp>
#include "Button.hpp"

// Classe représentant un bouton textuel sur l'interface SFML.
class TextButton: public Button {
    sf::RectangleShape shape;
    sf::Text text;

public:
    TextButton(int value, float relativeX, float relativeY, float width, float height, const std::string& label, sf::Font& font, int characterSize, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void setSelected(bool selected);
    void setString(std::string string);
    bool contains(const sf::Vector2f& point) const;
    void setPositionRelativeToWindow(float relativeX, float relativeY, sf::RenderWindow& window);
};