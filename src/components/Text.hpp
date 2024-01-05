#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Text {
    sf::Text text;
    sf::RectangleShape background;

public:
    Text(sf::Font& font, unsigned int characterSize, const std::string& str, const sf::Color& textColor, const sf::Color& backgroundColor, float relativeX, float relativeY, sf::RenderWindow& window);
    std::string getString() const;
    void setString(std::string str, float relativeX, float relativeY, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;
    void setPositionRelativeToWindow(float relativeX, float relativeY, sf::RenderWindow& window);
};
