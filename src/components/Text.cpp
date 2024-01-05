#include "Text.hpp"

Text::Text(sf::Font& font, unsigned int characterSize, const std::string& str, const sf::Color& textColor, const sf::Color& backgroundColor, float relativeX, float relativeY, sf::RenderWindow& window)
        : text(str, font, characterSize), background(sf::Vector2f(0.f, 0.f)) {
    text.setFillColor(textColor);
    background.setFillColor(backgroundColor);

    setPositionRelativeToWindow(relativeX, relativeY, window);
}

std::string Text::getString() const { return text.getString().toAnsiString(); }

void Text::setString(std::string str, float relativeX, float relativeY, sf::RenderWindow& window) {
    text.setString(str);
    setPositionRelativeToWindow(relativeX, relativeY, window);
}

// Dessine le texte et son fond sur la fenêtre.
void Text::draw(sf::RenderWindow& window) const {
    window.draw(background);
    window.draw(text);
}

// Modifie la position du texte selon la taille de fenêtre.
void Text::setPositionRelativeToWindow(float relativeX, float relativeY, sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();

    float xPos = relativeX * windowSize.x;
    float yPos = relativeY * windowSize.y;

    sf::FloatRect textBounds = text.getLocalBounds();

    background.setSize(sf::Vector2f(textBounds.width + 10.f, textBounds.height + 10.f));

    text.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    sf::FloatRect backgroundBounds = background.getLocalBounds();
    background.setOrigin(backgroundBounds.left + backgroundBounds.width / 2.f, backgroundBounds.top + backgroundBounds.height / 2.f);

    text.setPosition(xPos, yPos);
    background.setPosition(xPos, yPos);
}