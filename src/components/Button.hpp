#pragma once

#include <SFML/Graphics.hpp>

class Button {
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font& font;
    bool isSelected;

public:
    Button(float relativeX, float relativeY, float width, float height, const std::string& label, sf::Font& font, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void setSelected(bool selected);
    bool contains(const sf::Vector2f& point) const;
    bool getSelected() const;
    void setPositionRelativeToWindow(float relativeX, float relativeY, sf::RenderWindow& window);
};