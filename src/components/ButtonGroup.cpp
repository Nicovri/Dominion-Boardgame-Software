#include "ButtonGroup.hpp"

void ButtonGroup::addButton(int value, float relativeX, float relativeY, float width, float height, const std::string& label, sf::Font& font, int characterSize, sf::RenderWindow& window) {
    Button *button = new TextButton(value, relativeX, relativeY, width, height, label, font, characterSize, window);
    buttons.push_back(button);

    if(buttons.size() > 1) {
        buttons.back()->setSelected(false);
    }
}

void ButtonGroup::addButton(int value, float relativeX, float relativeY, float scale, sf::Texture& texture, sf::RenderWindow& window) {
    Button *button = new ImageButton(value, relativeX, relativeY, scale, texture, window);
    buttons.push_back(button);

    if(buttons.size() > 1) {
        buttons.back()->setSelected(false);
    }
}

void ButtonGroup::removeButton(int index) {
    if(index >= 0 && index <= int(buttons.size()-1)) {
        buttons.erase(buttons.begin() + index);
    }
}

void ButtonGroup::clear() {
    buttons.clear();
}

void ButtonGroup::draw(sf::RenderWindow& window) {
    for (Button *button : buttons) {
        button->draw(window);
    }
}

int ButtonGroup::getSelectedValue() const {
    for (std::size_t i = 0; i < buttons.size(); ++i) {
        if (buttons[i]->getSelected()) {
            return buttons[i]->getValue();
        }
    }
    return -1;
}

void ButtonGroup::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        for (Button *button : buttons) {
            if (button->contains(mousePos)) {
                button->setSelected(true);
                for (Button *otherButton : buttons) {
                    if (otherButton != button) {
                        otherButton->setSelected(false);
                    }
                }
                break;
            }
        }
    }
}