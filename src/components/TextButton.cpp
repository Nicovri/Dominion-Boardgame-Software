#include "TextButton.hpp"

TextButton::TextButton(int value, float relativeX, float relativeY, float width, float height, const std::string& label, sf::Font& font, sf::RenderWindow& window): Button(value) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::Black);

    this->setSelected(this->getSelected());

    text.setString(label);
    text.setFont(font);
    text.setCharacterSize(24);
    
    setPositionRelativeToWindow(relativeX, relativeY, window);
}

void TextButton::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

void TextButton::setSelected(bool selected) {
    Button::setSelected(selected);
    if (selected) {
        shape.setFillColor(sf::Color::Black);
        text.setFillColor(sf::Color::White);
    } else {
        shape.setFillColor(sf::Color::White);
        text.setFillColor(sf::Color::Black);
    }
}

bool TextButton::contains(const sf::Vector2f& point) const {
    return shape.getGlobalBounds().contains(point);
}

void TextButton::setPositionRelativeToWindow(float relativeX, float relativeY, sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    shape.setPosition(windowSize.x * relativeX - shape.getSize().x / 2.f, windowSize.y * relativeY - shape.getSize().y / 2.f);

    sf::FloatRect textBounds = text.getLocalBounds();
    sf::FloatRect shapeBounds = shape.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    text.setPosition(shape.getPosition() + sf::Vector2f(shapeBounds.width / 2.f, shapeBounds.height / 2.f));
}