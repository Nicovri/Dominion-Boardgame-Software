#pragma once

#include <SFML/Graphics.hpp>
#include "Button.hpp"

class ImageButton: public Button {
    sf::Sprite sprite;
    sf::Texture texture;

public:
    ImageButton(int value, float relativeX, float relativeY, float scale, const std::string& imagePath, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void setSelected(bool selected);
    bool contains(const sf::Vector2f& point) const;
    void setPositionRelativeToWindow(float relativeX, float relativeY, sf::RenderWindow& window);
};
