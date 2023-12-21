#include "TextInputField.hpp"

TextInputField::TextInputField(float relativeX, float relativeY, sf::Font& font, sf::RenderWindow& window): content("") {
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    inputField.setSize(sf::Vector2f(200.f, 30.f));
    inputField.setOutlineThickness(2.f);
    inputField.setFillColor(sf::Color::White);
    inputField.setOutlineColor(sf::Color::Black);

    setPositionRelativeToWindow(relativeX, relativeY, window);
}

void TextInputField::draw(sf::RenderWindow& window) {
    window.draw(inputField);
    window.draw(text);
}

void TextInputField::setPositionRelativeToWindow(float relativeX, float relativeY, sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    inputField.setPosition(windowSize.x * relativeX - inputField.getSize().x / 2.f, windowSize.y * relativeY - inputField.getSize().y / 2.f);
    text.setPosition(windowSize.x * relativeX - inputField.getSize().x / 2.f, windowSize.y * relativeY - inputField.getSize().y / 2.f);
}

void TextInputField::clear() {
    content = "";
    updateText();
}

void TextInputField::updateText() {
    text.setString(content);
}

const std::string& TextInputField::getContent() const {
    return content;
}

void TextInputField::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 && content.size() > 0) {
            content.pop_back();
        } else if (event.text.unicode >= 32 && event.text.unicode < 128) {
            content += static_cast<char>(event.text.unicode);
        }
        updateText();
    }
}