#include "ImageButton.hpp"

ImageButton::ImageButton(int value, float relativeX, float relativeY, float scale, const std::string& imagePath, sf::RenderWindow& window) : Button(value) {
    if (!texture.loadFromFile(imagePath)) {
        // Handle error loading texture
    }

    this->setSelected(this->getSelected());

    sprite.setTexture(texture);
    sprite.setScale(scale, scale);
    setPositionRelativeToWindow(relativeX, relativeY, window);
}

void ImageButton::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void ImageButton::setSelected(bool selected) {
    Button::setSelected(selected);
    if(selected) {
        sprite.setColor(sf::Color::White);
    } else {
        sprite.setColor(sf::Color(75, 75, 75));
    }
}

bool ImageButton::contains(const sf::Vector2f& point) const {
    return sprite.getGlobalBounds().contains(point);
}

void ImageButton::setPositionRelativeToWindow(float relativeX, float relativeY, sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    sprite.setPosition(windowSize.x * relativeX, windowSize.y * relativeY);
}
