#include "ImageButton.hpp"

ImageButton::ImageButton(int value, float relativeX, float relativeY, float scale, sf::Texture& texture, sf::RenderWindow& window) : Button(value) {
    this->setSelected(this->getSelected());

    sprite.setTexture(texture);
    sprite.setScale(scale, scale);
    setPositionRelativeToWindow(relativeX, relativeY, window);
}

// Dessine le bouton sur la fenêtre.
void ImageButton::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

// Modifie la valeur de selection de ce bouton. Modifie son design en fonction.
void ImageButton::setSelected(bool selected) {
    Button::setSelected(selected);
    if(selected) {
        sprite.setColor(sf::Color::White);
    } else {
        sprite.setColor(sf::Color(100, 100, 100));
    }
}

// Le bouton contient-il un certain point de la fenêtre (notamment la position de la souris)?
bool ImageButton::contains(const sf::Vector2f& point) const {
    return sprite.getGlobalBounds().contains(point);
}

// Modifie la position du bouton selon la taille de fenêtre.
void ImageButton::setPositionRelativeToWindow(float relativeX, float relativeY, sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    sprite.setPosition(windowSize.x * relativeX, windowSize.y * relativeY);
}
