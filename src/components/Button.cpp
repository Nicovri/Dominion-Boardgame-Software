#include "Button.hpp"

Button::Button(float relativeX, float relativeY, float width, float height, const std::string& label, sf::Font& font, sf::RenderWindow& window): font(font), isSelected(true) {
    shape.setSize(sf::Vector2f(width, height));
    setPositionRelativeToWindow(relativeX, relativeY, window);
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::Black);

    this->setSelected(isSelected);

    text.setString(label);
    text.setFont(font);
    text.setCharacterSize(24);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    text.setPosition(shape.getPosition() + sf::Vector2f(width / 2.f, height / 2.f));
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

void Button::setSelected(bool selected) {
    isSelected = selected;
    if (isSelected) {
        shape.setFillColor(sf::Color::Black);
        text.setFillColor(sf::Color::White);
    } else {
        shape.setFillColor(sf::Color::White);
        text.setFillColor(sf::Color::Black);
    }
}

bool Button::contains(const sf::Vector2f& point) const {
    return shape.getGlobalBounds().contains(point);
}

bool Button::getSelected() const {
    return isSelected;
}

void Button::setPositionRelativeToWindow(float relativeX, float relativeY, sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    shape.setPosition(windowSize.x * relativeX - shape.getSize().x / 2.f, windowSize.y * relativeY - shape.getSize().y / 2.f);
}