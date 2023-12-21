#include "ButtonGroup.hpp"

void ButtonGroup::addButton(float relativeX, float relativeY, float width, float height, const std::string& label, sf::Font& font, sf::RenderWindow& window, int value) {
    Button button(relativeX, relativeY, width, height, label, font, window);
    buttonValues.push_back(value);
    buttons.push_back(button);

    if(buttons.size() > 1) {
        buttons.back().setSelected(false);
    }
}

void ButtonGroup::draw(sf::RenderWindow& window) {
    for (Button& button : buttons) {
        button.draw(window);
    }
}

int ButtonGroup::getSelectedValue() const {
    for (std::size_t i = 0; i < buttons.size(); ++i) {
        if (buttons[i].getSelected()) {
            return buttonValues[i];
        }
    }
    return -1;
}

void ButtonGroup::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        for (auto& button : buttons) {
            if (button.contains(mousePos)) {
                button.setSelected(true);
                for (auto& otherButton : buttons) {
                    if (&otherButton != &button) {
                        otherButton.setSelected(false);
                    }
                }
                break;
            }
        }
    }
}